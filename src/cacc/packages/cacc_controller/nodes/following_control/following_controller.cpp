#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <packetHandler.h>
#include <carFollowing.h>
#include <std_msgs/Float64.h>
using namespace std;

// #define JUDEMODEL
#define PRARXMODEL
//#define GIPPSMODEL

#define DEBUG

// Variables for communication
int id[2];
int idx[2];
unsigned int checksum = 0;

StatePacketListener* state_packet_listener[2];
StatePacketSpeaker* predicted_state_packet_speaker;
StatePacketSpeaker* curr_state_packet_speaker;
StatePacketSpeaker* state_error_packet_speaker;
ControlPacketSpeaker* control_packet_speaker;
cacc_msgs::CaccStatePacket cacc_state_packet_msg[2];
cacc_msgs::CaccStatePacket cacc_predicted_state_packet_msg;
cacc_msgs::CaccStatePacket cacc_curr_state_packet_msg;
cacc_msgs::CaccStatePacket cacc_state_error_packet_msg;
cacc_msgs::CaccControlPacket cacc_control_packet_msg;

std::string state_packet_topic[2];

bool using_sensor_flag;
bool using_custom_topic_flag;

// CSV output
bool                                            Flag_csv_output = false;
std::string                                     output_csv_folder;

#ifdef JUDEMODEL
    JudeModel driver(0.1, 2.0, 0.0);
#elif defined PRARXMODEL
    PrarxModel driver(0.1, 0.5, -0.5);
#elif defined GIPPSMODEL
    GippsModel driver(0.1);
#endif

int main(int argc, char** argv)
{
    ros::init(argc, argv, "following_controller");

    //Initialize pointers
    for(int i=0; i<2; i++){
        state_packet_listener[i] = NULL;
    }
    predicted_state_packet_speaker = NULL;
    curr_state_packet_speaker = NULL;
    state_error_packet_speaker = NULL;
    control_packet_speaker = NULL;

    //Node handles
    ros::NodeHandle nh;
    ros::NodeHandle private_nh("~");

    private_nh.param<bool>("using_sensor_flag", using_sensor_flag, false);
    private_nh.param<bool>("using_custom_topic_flag", using_custom_topic_flag, false);
    private_nh.param<std::string>("state_packet_leader", state_packet_topic[0], "CarFollowing_Car_0/state_packet");
    private_nh.param<std::string>("state_packet_follower", state_packet_topic[1], "CarFollowing_Car_1/state_packet");

    private_nh.param<bool>("Flag_csv_output", Flag_csv_output, true);
    private_nh.param<std::string>("output_csv_folder", output_csv_folder, "/home/thori/log/sim/range");

    // Open CSV file
    std::ofstream myfile;
    time_t now = time(NULL);
    tm* now_local = localtime(&now);

    if(Flag_csv_output){
        char str[256];
        strftime(str,sizeof(str)-1,"%Y%m%d_%H%M%S",now_local);    
        string date_str(str);
        string filename = output_csv_folder + "/data_following_" + date_str + ".csv";
        myfile.open (filename);
        myfile << "Time,range,input,P1,P2\n";
    }

    double time_exp_start;
    time_exp_start = ros::Time::now().toSec();

    //Set up id, listener, and speaker
    for(int ic = 0; ic < 2; ic++){
        private_nh.param<int>("idx_"+std::to_string(ic), idx[ic], ic);
        private_nh.param<int>("id_"+std::to_string(idx[ic]), id[ic], idx[ic]);
        state_packet_listener[ic] = new StatePacketListener(idx[ic], id[ic], "CarFollowing", state_packet_topic[ic]); 
        if(ic == 1){
            control_packet_speaker = new ControlPacketSpeaker(idx[ic], id[ic]);
            curr_state_packet_speaker = new StatePacketSpeaker(idx[ic], id[ic], "CarFollowing", StatePacketType::CURRENT); 
            state_error_packet_speaker = new StatePacketSpeaker(idx[ic], id[ic], "CarFollowing", StatePacketType::ERROR); 
            predicted_state_packet_speaker = new StatePacketSpeaker(idx[ic], id[ic], "CarFollowing", StatePacketType::PREDICT); 
        }
    }

    ros::Publisher TTC_pub = nh.advertise<std_msgs::Float64>("CarFollowing_TTC", 1);
    ros::Publisher THW_pub = nh.advertise<std_msgs::Float64>("CarFollowing_THW", 1);

/////////////////////////////////////////////////////////////////////////////
    //ROS loop
    ros::Rate loop_rate(100);
    while(ros::ok()){
        ros::spinOnce();

        //Get sensor info
        for(int ic = 0; ic < 2; ic++){
            state_packet_listener[ic]->get_cacc_state_packet_msg(&cacc_state_packet_msg[ic]);
        }
        
        //Set the states
        if(using_sensor_flag){
            driver.setMeasurement(ros::Time::now(),cacc_state_packet_msg[1].speed,cacc_state_packet_msg[1].acceleration,
                    cacc_state_packet_msg[1].distance,cacc_state_packet_msg[0].speed-cacc_state_packet_msg[1].speed);
        }
        else{
            driver.setMeasurement(ros::Time::now(),cacc_state_packet_msg[1].speed,cacc_state_packet_msg[1].acceleration,
                    cacc_state_packet_msg[1].distance);
        }

        //Calculate the control inputs
        double vel_ref, acc_ref, P;
        vel_ref = driver.getOutputSpeed();
#ifdef JUDEMODEL
        acc_ref = driver.getOutputAcceleration(0.1);
#elif defined PRARXMODEL
        acc_ref = driver.getOutputAcceleration();
        P = driver.getProbability();
#elif defined GIPPSMODEL
        acc_ref = driver.getOutputAcceleration();
#endif

        //Publish the results
        // Control input
        cacc_control_packet_msg.id = id[1];
        cacc_control_packet_msg.vel_ref = vel_ref;
        cacc_control_packet_msg.acc_ref = acc_ref;
        cacc_control_packet_msg.checksum = checksum;
        control_packet_speaker->publish_cacc_control_packet_msg(cacc_control_packet_msg);                

        // Current state
        cacc_curr_state_packet_msg = cacc_state_packet_msg[1];
        cacc_curr_state_packet_msg.distance = driver.getRange();
        cacc_curr_state_packet_msg.speed = driver.getSpeed();
        cacc_curr_state_packet_msg.acceleration = driver.getAcceleration();
        curr_state_packet_speaker->publish_cacc_state_packet_msg(cacc_curr_state_packet_msg);
    

        std_msgs::Float64 TTC_msg, THW_msg;
        TTC_msg.data = driver.getInversedTTC();
        THW_msg.data = driver.getTHW();
        THW_pub.publish(THW_msg);
        TTC_pub.publish(TTC_msg);

        // //print out
        // std::cout<<"///////////////////////////////////////////////"<<std::endl;
        // for(int ic = 0; ic < 1; ic++){
        //     std::cout<<"------Car "<<ic<<"-----------"<<std::endl
        //             <<"Range = "<<driver.getRange()<<std::endl
        //             <<"Range rate = "<<driver.getRangeRate()<<std::endl
        //             <<"Speed = "<<driver.getSpeed()<<std::endl
        //             <<"THW = "<<driver.getTHW()<<std::endl
        //             <<"1/TTC = "<<driver.getInversedTTC()<<std::endl
        //             <<"Vel_ref = "<<vel_ref<<std::endl
        //             <<"Acc_ref = "<<acc_ref<<std::endl
        //             <<"--------------------------"<<std::endl;
        // }

        if(Flag_csv_output){
            myfile <<ros::Time::now().toSec()-time_exp_start<<","<<driver.getRange()<<","<<acc_ref<<","<<1-P<<","<<P<<endl;   
        }

        checksum++;

        loop_rate.sleep();
    }

    
    //Delete pointers
    for(int i=0; i<2; i++){
        if(state_packet_listener[i] != NULL){
            delete state_packet_listener[i];
            state_packet_listener[i] = NULL;
        }
    }
    if(control_packet_speaker != NULL){
        delete control_packet_speaker;
        control_packet_speaker = NULL;
    }
    if(predicted_state_packet_speaker != NULL){
        delete predicted_state_packet_speaker;
        predicted_state_packet_speaker = NULL;
    }
    if(curr_state_packet_speaker != NULL){
        delete curr_state_packet_speaker;
        curr_state_packet_speaker = NULL;
    }
    
    return 0;
};