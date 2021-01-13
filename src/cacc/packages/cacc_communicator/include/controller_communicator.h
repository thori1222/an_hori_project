#ifndef CONTROLLER_COMMUNICATOR_H_
#define CONTROLLER_COMMUNICATOR_H_

#include <udp_connector_lib/udp_connector.h>
#include <Course.h>

#include <FrenetCoordinate.h>

#pragma pack(1)
#include <cacc_msgs/CaccControlPacket.h>
#include <cacc_msgs/CaccSensorPacket.h>
#pragma pack()

namespace Udp_ns{

class ControllerSender : public UdpSender{
public:
    ControllerSender(int _id, std::string _destination, unsigned short _port);
    ~ControllerSender();
    void run();

private:
    //Node handles
    ros::NodeHandle nh;
	ros::NodeHandle private_nh;
    
    int id;
    unsigned int checksum;
    bool com_flag;
    int com_cnt;

    //-------------------To send------------------------//
    //ControlInfo
    ros::Subscriber cacc_control_packet_sub;
    cacc_msgs::CaccControlPacket cacc_control_packet_msg;
    cacc_msgs::CaccControlPacket cacc_control_packet_msg_prev;
    void caccControlPacketCallback(const cacc_msgs::CaccControlPacket& msg);
    void caccControlPacketSend(const cacc_msgs::CaccControlPacket& msg);
};

class ControllerReceiver : public UdpReceiver{
public:
	ControllerReceiver(int _id, unsigned short _port);
	~ControllerReceiver();
	void run();

    RTCLib::FrenetCoordinate2D lane_center;
    RTCLib::CacheToFrenet cache_to_g;
    double length;
    double lane_u;
    double lane_v;
    double theta_d_lane;
    double theta_e_lane;

private:
	//Node handles
    ros::NodeHandle nh;
	ros::NodeHandle private_nh;

    int id;
    bool com_flag;
    int com_cnt;

    CarManagement::Course* course;
    std::string course_file;

    //-------------------To receive----------------------//
    //SensorInfo
    ros::Publisher cacc_sensor_packet_pub;
    cacc_msgs::CaccSensorPacket cacc_sensor_packet_msg;
    cacc_msgs::CaccSensorPacket cacc_sensor_packet_msg_prev;
	void caccSensorPacketReceive();
};

}
#endif
