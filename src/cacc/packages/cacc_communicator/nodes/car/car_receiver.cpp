#include <car_communicator.h>

namespace Udp_ns{
CarReceiver::CarReceiver(unsigned short _port):private_nh("~"),UdpReceiver(_port){
	private_nh.param<int>("id", id, 1101);
    private_nh.param<bool>("manual", manual, false);
    private_nh.param<std::string>("twist_cmd_topic", twist_cmd_str, "/twist_cmd");
	private_nh.param<std::string>("accel_cmd_topic", accel_cmd_str, "/control/accel");
	private_nh.param<std::string>("com_status_topic", com_status_str, "/com_status");
	
	twist_cmd_pub = nh.advertise<geometry_msgs::TwistStamped>(twist_cmd_str, 1);
	accel_cmd_pub = nh.advertise<std_msgs::Float64>(accel_cmd_str, 1);
	com_status_pub = nh.advertise<std_msgs::Int32>(com_status_str, 1);
	cacc_control_packet_pub = nh.advertise<cacc_msgs::CaccControlPacket>("cacc_control_packet", 1);

    com_flag = true;
	com_cnt = 0;
	com_status = 0;
};

CarReceiver::~CarReceiver(){
	close(socket_var);
};

void CarReceiver::caccControlPacketReceive(){
	recv(socket_var, &cacc_control_packet_msg, sizeof(cacc_control_packet_msg), 0); 
	
	if(cacc_control_packet_msg.checksum - cacc_control_packet_msg_prev.checksum == 0){
        if(com_cnt >= UPDATE_LIMIT){
			ROS_ERROR("Wireless communication has not been updated.");
			com_flag = false;
			com_cnt = 0;
			com_status = 2;
		}
		else{
			com_cnt++;
		}
	}
	else{
		com_flag = true;
		com_cnt = 0;
		com_status = 1;
	} 

	if(com_cnt > CHECKSUM_LIMIT){
	//if(cacc_control_packet_msg.checksum - cacc_control_packet_msg_prev.checksum > CHECKSUM_LIMIT)
		ROS_ERROR("Wireless communication has been delayed more than %d packets.", CHECKSUM_LIMIT);
		com_status = 0;
	}
    cacc_control_packet_msg_prev = cacc_control_packet_msg;
};

void CarReceiver::run(){
	if(!manual){
		ros::Rate loop_rate(100); //100Hz
		while(ros::ok()){
			caccControlPacketReceive();
			
			if(com_flag){
				if(cacc_control_packet_msg.id != id){
					ROS_ERROR("Incorrect ID on control packet has been received to CarReceiver. ID of the message is not matched to the receiver ID.");
					ROS_ERROR("ID on the receiver: %d, ID in the message: %d", id, cacc_control_packet_msg.id);
				}
				else{
					twist_cmd_msg.header.stamp = ros::Time::now();
					twist_cmd_msg.twist.linear.x = cacc_control_packet_msg.vel_ref;
					twist_cmd_pub.publish(twist_cmd_msg);

					accel_cmd_msg.data = cacc_control_packet_msg.acc_ref;
					accel_cmd_pub.publish(accel_cmd_msg);

					cacc_control_packet_pub.publish(cacc_control_packet_msg);

				}
			}
			
			com_status_msg.data = com_status;
			com_status_pub.publish(com_status_msg);

			loop_rate.sleep();
		}
	}
};

};

int main(int argc, char** argv){
	ros::init(argc, argv, "car_receiver");

	int port;

	ros::NodeHandle private_nh("~");

	private_nh.param<int>("port_receive", port, 54750);

	Udp_ns::CarReceiver car_receiver(port);

	car_receiver.run();

	return 0;
}
