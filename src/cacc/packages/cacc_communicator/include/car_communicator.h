#ifndef CAR_COMMUNICATOR_H_
#define CAR_COMMUNICATOR_H_

#include <udp_connector_lib/udp_connector.h>

#include <ros/ros.h>
#include <tf/tf.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <dynamic_reconfigure/server.h>
#include <cacc_communicator/carParamConfig.h>

#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/TwistWithCovarianceStamped.h>
#include <geometry_msgs/PoseStamped.h>
#pragma pack(1)
#include <cacc_msgs/CaccControlPacket.h>
#include <cacc_msgs/CaccSensorPacket.h>
#pragma pack()

namespace Udp_ns{

enum TwistType{
    TWIST_STAMPED = 1,
    TWIST_WITH_COVARIANCE_STAMPED = 2,
};

class CarSender : public UdpSender{
public:
    CarSender(std::string _destination, unsigned short _port);
    ~CarSender();
    void run();

private:
    //Node handles
    ros::NodeHandle nh;
	ros::NodeHandle private_nh;
    
    // //Log file
    // std::string filename;
    // std::ofstream ofs;
	
    int id;
    bool manual;
    float thw;
    // float alpha;
    // float beta;
    // float tau[4]; //time constant on vehicle model (acc_0mph, acc_10mph, dec_10mph, dec_20mph)
    // float K[4];
    float tau; //time constant on vehicle model
    float K;
    float sensor2frontbumper;
    float sensor2rearbumper;
    int vel_gain;
    int vel_gain_low;
    int vel_gain_dec;
    unsigned int checksum;
    TwistType twist_type;
    std::string twist_type_str;

    //Acceleration calculated from velocity
    ros::Time t_now, t_prev;
    ros::Duration time_diff;
    double dt;

    //THW dynamic reconfigurer
    dynamic_reconfigure::Server<cacc_communicator::carParamConfig> server;
    dynamic_reconfigure::Server<cacc_communicator::carParamConfig>::CallbackType f;

    //-------------------To send------------------------//
    //SensorInfo
    ros::Subscriber radar_sub;
    ros::Subscriber curr_pose_sub;
    ros::Subscriber curr_twist_sub;
    ros::Publisher  cacc_sensor_packet_pub;
    std::string radar_str;
    std::string curr_pose_str;
    std::string curr_twist_str;
    cacc_msgs::CaccSensorPacket cacc_sensor_packet_msg;
    void radarCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void currPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg);
    void currTwistCallback(const geometry_msgs::TwistStamped::ConstPtr& msg);
    void currTwistWithCovarianceCallback(const geometry_msgs::TwistWithCovarianceStamped::ConstPtr& msg);
    void caccSensorPacketSend(const cacc_msgs::CaccSensorPacket& msg);
    void carParamConfigCallback(cacc_communicator::carParamConfig &config, uint32_t level);
};

class CarReceiver : public UdpReceiver{
public:
	CarReceiver(unsigned short _port);
	~CarReceiver();
	void run();

private:
	//Node handles
    ros::NodeHandle nh;
	ros::NodeHandle private_nh;
    
	int id;
    bool manual;
    bool com_flag;
    int com_cnt;  
    int com_status;  //0: not updated, 1: normal, 2: delayed

    //-------------------To receive----------------------//
    //ControlInfo
    ros::Publisher twist_cmd_pub; 
    ros::Publisher accel_cmd_pub; 
    ros::Publisher com_status_pub;
    ros::Publisher cacc_control_packet_pub;
    std::string twist_cmd_str;
    std::string accel_cmd_str;
    std::string com_status_str;
	std_msgs::Float64 accel_cmd_msg;
    std_msgs::Int32 com_status_msg;
    geometry_msgs::TwistStamped twist_cmd_msg;
    cacc_msgs::CaccControlPacket cacc_control_packet_msg;
    cacc_msgs::CaccControlPacket cacc_control_packet_msg_prev;
    void caccControlPacketReceive();
};

}
#endif
