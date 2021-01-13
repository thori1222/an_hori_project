#include <controller_communicator.h>
#define DEBUG
#define FRENET

namespace Udp_ns{
    
ControllerReceiver::ControllerReceiver(int _id, unsigned short _port):private_nh("~"),UdpReceiver(_port){
    id = _id;

    //Set course
    private_nh.param<std::string>("course_file", course_file, "course.txt");
    try{
#ifdef FRENET
        lane_center.LoadPathFromCSV(course_file, true);
        lane_center = lane_center.ResampleConservative(0.01);
        length = lane_center.length;

        lane_u = 0;
        lane_v = 0;
        theta_d_lane = 0;
        theta_e_lane = 0;
#else
        course = new CarManagement::Course(course_file);
#endif
    }
    catch(std::exception e){
        ROS_ERROR("Exception occured during loading course file.");
#ifndef FRENET
        delete course;
#endif
        ros::shutdown();
    }
    //Setting for ROS
    cacc_sensor_packet_pub = nh.advertise<cacc_msgs::CaccSensorPacket>("cacc_sensor_packet", 1);

    com_flag = true;
    com_cnt = 0;
};
        
ControllerReceiver::~ControllerReceiver(){
    if(course != NULL){
        delete course;
        course = NULL;
    }

    close(socket_var);
};
    
void ControllerReceiver::caccSensorPacketReceive(){
#ifdef DEBUG
    std::cout<<"caccSensorPacketReceive called."<<std::endl;
#endif
    recv(socket_var, &cacc_sensor_packet_msg, sizeof(cacc_sensor_packet_msg), 0); 

    if(cacc_sensor_packet_msg.checksum - cacc_sensor_packet_msg_prev.checksum == 0){
        if(com_cnt >= UPDATE_LIMIT){
            ROS_ERROR("Wireless communication has not been updated.");
            com_flag = false;
            com_cnt = 0;
        }
        else{
            com_cnt++;
        }
    }
    else{
        com_flag = true;
        com_cnt = 0;
    }

    if(cacc_sensor_packet_msg.checksum - cacc_sensor_packet_msg_prev.checksum > CHECKSUM_LIMIT)
        ROS_ERROR("Wireless communication has been delayed more than %d packets.", CHECKSUM_LIMIT);

    cacc_sensor_packet_msg_prev = cacc_sensor_packet_msg;
};    
    
void ControllerReceiver::run(){
    ros::Rate loop_rate(100);
#ifdef DEBUG
    std::cout<<"node started."<<std::endl;
#endif
    while(ros::ok()){
        ros::spinOnce();
        caccSensorPacketReceive(); 
        if(com_flag){      
            if(cacc_sensor_packet_msg.id != id){
            ROS_ERROR("Incorrect ID on sensor packet has been received to ControllerReceiver. ID of the message is not matched to the receiver ID.");
            ROS_ERROR("ID on the receiver: %d, ID in the message: %d", id, cacc_sensor_packet_msg.id);
            }
            else{
#ifdef DEBUG
    std::cout<<"calculating the course coordinate..."<<std::endl;
#endif
                // Convert xy coordinate to uv coordinate
                double x = cacc_sensor_packet_msg.x, y = cacc_sensor_packet_msg.y, yaw = cacc_sensor_packet_msg.yaw;
                double u,v,w;
#ifdef FRENET
                cache_to_g = lane_center.GetFrenet(x, y, yaw+M_PI/2, lane_u, lane_v, theta_e_lane, cache_to_g);

                RTCLib::FrenetPoint2D lc_point = lane_center.GetPoint(cache_to_g);
                theta_d_lane = lc_point.to_next_theta;
	    	    u = lane_u;
    	    	v = lane_v;
#else
                course->XYZ2UVW(x, y, 0, &u, &v, &w);
#endif
                cacc_sensor_packet_msg.u = u;
                cacc_sensor_packet_msg.v = v;

                // Publish
                cacc_sensor_packet_pub.publish(cacc_sensor_packet_msg);
            }
        }
        loop_rate.sleep();
    }
};
  
};

int main(int argc, char** argv){
    ros::init(argc, argv, "controller_receiver");

    int id;
    int port;

    ros::NodeHandle private_nh("~");
    private_nh.param<int>("id", id, 0);
    private_nh.param<int>("port_receive", port, 54650);
    
    Udp_ns::ControllerReceiver controller_receiver(id, port);
    controller_receiver.run();
    
    return 0;
}
