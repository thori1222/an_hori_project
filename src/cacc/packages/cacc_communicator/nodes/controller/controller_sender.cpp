#include <controller_communicator.h>

namespace Udp_ns{
    
ControllerSender::ControllerSender(int _id, std::string _destination, unsigned short _port):private_nh("~"),UdpSender(_destination, _port){
    id = _id;
    checksum = 0;
    com_flag = true;
    com_cnt = 0;

    //Setting for ROS
    cacc_control_packet_sub = nh.subscribe("cacc_control_packet", 1, &Udp_ns::ControllerSender::caccControlPacketCallback, this);
    
};
    
ControllerSender::~ControllerSender(){
    close(socket_var);
};
    
void ControllerSender::caccControlPacketCallback(const cacc_msgs::CaccControlPacket& msg){
    if(msg.checksum == cacc_control_packet_msg_prev.checksum){
        if(com_cnt >= UPDATE_LIMIT){
            ROS_ERROR("Control packet has not been updated.");	
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
    if(msg.checksum - cacc_control_packet_msg_prev.checksum > CHECKSUM_LIMIT)
		ROS_ERROR("Control packet update has been delayed more than %d packets.", CHECKSUM_LIMIT);
    
    cacc_control_packet_msg_prev = msg;
    cacc_control_packet_msg = msg;
    cacc_control_packet_msg.checksum = checksum;
};
    
void ControllerSender::caccControlPacketSend(const cacc_msgs::CaccControlPacket& msg){
    int packet_length = sizeof(msg);
    if( sendto(socket_var, &msg, packet_length, 0, (const sockaddr*)&sock_addr, sizeof(sock_addr)) < 0 )
    {
      ROS_ERROR("Cannot send command!" );
    }
};
    
void ControllerSender::run(){
    ros::Rate loop_rate(100);
    while(ros::ok()){
        ros::spinOnce();
        
        if(com_flag && cacc_control_packet_msg.id != id){
            ROS_ERROR("Incorrect ID on control packet has been received to ControllerSender. ID of the message is not matched to the sender ID.");
            ROS_ERROR("ID on the sender: %d, ID in the message: %d", id, cacc_control_packet_msg.id);
        }
        else{
            caccControlPacketSend(cacc_control_packet_msg);
        }
        checksum++;

        loop_rate.sleep();
    }
};

};

int main(int argc, char** argv){
    ros::init(argc, argv, "controller_sender");
    
    int id;
    bool manual;
    std::string destination;
    int port;

    ros::NodeHandle private_nh("~");

    private_nh.param<int>("id", id, 0);
    private_nh.param<bool>("manual", manual, false);
    private_nh.param<std::string>("destination", destination, "192.168.13.52");
    private_nh.param<int>("port_send", port, 54750);

    if(!manual){
        Udp_ns::ControllerSender controller_sender(id, destination, port);
        controller_sender.run();    
    }
    
    return 0;
}
