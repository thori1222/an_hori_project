#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

#include <ros/ros.h>
#include <packetHandler.h>
#include <modelEstimator.h>

#define FREQUENCY 10
#define DELAY 0.3

// Variables for communication
int id[2];
int idx[2];

StatePacketListener* state_packet_listener[2];
cacc_msgs::CaccStatePacket cacc_state_packet_msg[2];
std::string state_packet_topic[2];

bool using_sensor_flag;
double range_rate = 0.0;
double range_prev = 0.0;
ros::Time time_now, time_prev;

ModelEstimator* estimator;

std::vector<std::vector<double> > phis;

int main(int argc, char** argv)
{
    ros::init(argc, argv, "model_estimator");

    //Initialize pointers
    estimator = new ModelEstimator(0.3, 0.1);

    for(int i=0; i<2; i++){
        state_packet_listener[i] = NULL;
    }

    //Node handles
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    private_nh.param<bool>("using_sensor_flag", using_sensor_flag, false);
    private_nh.param<std::string>("state_packet_leader", state_packet_topic[0], "CarFollowing_Car_0/state_packet");
    private_nh.param<std::string>("state_packet_follower", state_packet_topic[1], "CarFollowing_Car_1/state_packet");

    //Set up id, listener
    for(int ic = 0; ic < 2; ic++){
        private_nh.param<int>("idx_"+std::to_string(ic), idx[ic], ic);
        private_nh.param<int>("id_"+std::to_string(idx[ic]), id[ic], idx[ic]);
        state_packet_listener[ic] = new StatePacketListener(idx[ic], id[ic], "CarFollowing", state_packet_topic[ic]); 
    }

    estimator->init();
    time_prev = ros::Time::now();
    int buffer_size = (int)(DELAY*FREQUENCY);
    ROS_INFO("buffer size was set as %d.", buffer_size);
    if(buffer_size == 0){
        ROS_WARN("buffer size was set as %d. It has changed to 1.", buffer_size);
        buffer_size = 1;
    }

/////////////////////////////////////////////////////////////////////////////
    //ROS loop
    ros::Rate loop_rate(10);
    while(ros::ok()){
        time_now = ros::Time::now();
        ros::spinOnce();

        //Get sensor info
        for(int ic = 0; ic < 2; ic++){
            state_packet_listener[ic]->get_cacc_state_packet_msg(&cacc_state_packet_msg[ic]);
        }
        
        //Set the states
        std::vector<double> phi;
        double y;

        double range = cacc_state_packet_msg[1].distance;
        double dt = (time_now - time_prev).toSec();
        range_rate = 0.9*range_rate + 0.1*(range - range_prev)/(dt<0.001?0.001:dt);

        phi.push_back(range);
        phi.push_back(using_sensor_flag?cacc_state_packet_msg[0].speed-cacc_state_packet_msg[1].speed:range_rate);
        phi.push_back(cacc_state_packet_msg[1].acceleration);
        phi.push_back((double)1.0);

        y = cacc_state_packet_msg[1].acceleration;

        phis.push_back(phi);
#ifdef DEBUG
        ROS_INFO("phi: [%f, %f, %f, %f]", phi[0], phi[1], phi[2], phi[3]);
        ROS_INFO("phis: %d / %d", phis.size(), buffer_size);
#endif
        
        if((int)(phis.size()) > buffer_size){
            while((int)(phis.size()) > buffer_size){
                phis.erase(phis.begin());
            }
        }
        
        //Add data to the estimator
        if((int)(phis.size()) == buffer_size){
            estimator->addData(*phis.begin(), y);
#ifdef DEBUG
            ROS_INFO("=======DATA ADDED=====");
            ROS_INFO("phi: \n[%f, %f, %f, %f]", (phis.begin()+2)->at(0), (phis.begin()+2)->at(1), (phis.begin()+2)->at(2), (phis.begin()+2)->at(3));
            ROS_INFO("y: \n%f", y);
#endif
        }

        //Update and publish params
        estimator->update();
        estimator->publishParams();


        //Backup data
        range_prev = range;
        time_prev = time_now;
        loop_rate.sleep();
    }

    
    //Delete pointers
    for(int i=0; i<2; i++){
        if(state_packet_listener[i] != NULL){
            delete state_packet_listener[i];
            state_packet_listener[i] = NULL;
        }
    }
    delete estimator;
    
    return 0;
};