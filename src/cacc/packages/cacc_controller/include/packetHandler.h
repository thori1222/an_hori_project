#ifndef PACKET_HANDLER_H_
#define PACKET_HANDLER_H_
#pragma once

#include <ros/ros.h>

#pragma pack(1)
#include <cacc_msgs/CaccControlPacket.h>
#include <cacc_msgs/CaccSensorPacket.h>
#include <cacc_msgs/CaccStatePacket.h>
#include <cacc_msgs/CaccMpcParam.h>
#include <cacc_msgs/CaccMpcState.h>
#pragma pack()

enum PositionType{
    DETECTION = 1,
    LOCALIZATION = 2,
    COMBINED = 3,
};

struct MpcParameter{
	float Ds;
	float Dmin;
	
	float umax;
	float umin;

	int q[3];
	int r;
	int sf; //ratio of sf to q
	int su;
	int sd;

	MpcParameter(){
		Ds   = 0.5;
		Dmin = 0.3;

		umax = 1.0;
		umin = -1.0;

		q[0] = 30;
		q[1] = 1;
		q[2] = 1;
		r    = 80;
		sf	 = 100;
		su	 = 1000;
		sd   = 1000;
	}
};

class SensorPacketListener{
public:
    ros::NodeHandle nh;
    int id;
    SensorPacketListener(int _car, int _id){
        id = _id;
        cacc_sensor_packet_sub = nh.subscribe("/Car_"+std::to_string(_car)+"/cacc_sensor_packet", 5, &SensorPacketListener::caccSensorPacketCallback, this);
    };
    void get_cacc_sensor_packet_msg(cacc_msgs::CaccSensorPacket* msg){
        *msg = cacc_sensor_packet_msg;
    }

private:
    ros::Subscriber cacc_sensor_packet_sub;
    cacc_msgs::CaccSensorPacket cacc_sensor_packet_msg;
    void caccSensorPacketCallback(const cacc_msgs::CaccSensorPacket& msg){
        cacc_sensor_packet_msg = msg;
        if(cacc_sensor_packet_msg.id != id){
            ROS_ERROR("Incorrect ID on sensor packet has been received to SensorPacketListener. ID of the message is not matched to the listener ID.");
            ROS_ERROR("ID on the listener: %d, ID in the message: %d", id, cacc_sensor_packet_msg.id);
        }
    }
};

class ControlPacketSpeaker{
private:
    ros::Publisher cacc_control_packet_pub;
    cacc_msgs::CaccControlPacket cacc_control_packet_msg;

public:
    ros::NodeHandle nh;
    int id;
    ControlPacketSpeaker(int _car, int _id){
        id = _id;
        cacc_control_packet_pub = nh.advertise<cacc_msgs::CaccControlPacket>("/Car_"+std::to_string(_car)+"/cacc_control_packet", 1);
    };
    void publish_cacc_control_packet_msg(const cacc_msgs::CaccControlPacket& msg){
        cacc_control_packet_msg = msg;
        
        cacc_control_packet_pub.publish(cacc_control_packet_msg);
    }
};

enum StatePacketType{
    NORMAL = 0,
    ERROR = 1,
    CURRENT = 2,
    PREDICT = 3,
};

class StatePacketSpeaker{
private:
    ros::Publisher cacc_state_packet_pub;
    cacc_msgs::CaccStatePacket cacc_state_packet_msg;

public:
    ros::NodeHandle nh;
    int id;
    std::string mode;
    StatePacketSpeaker(int _car, int _id, std::string _mode){
        id = _id;
        mode = _mode;
        cacc_state_packet_pub = nh.advertise<cacc_msgs::CaccStatePacket>(mode+"_Car_"+std::to_string(_car)+"/state_packet", 1);
    };
    StatePacketSpeaker(int _car, int _id, std::string _mode, bool _predict){
        id = _id;
        mode = _mode;
        if(_predict) cacc_state_packet_pub = nh.advertise<cacc_msgs::CaccStatePacket>(mode + "_Car_"+std::to_string(_car)+"/predicted_state_packet", 1);
        else cacc_state_packet_pub = nh.advertise<cacc_msgs::CaccStatePacket>(mode+"_Car_"+std::to_string(_car)+"/curr_state_packet", 1);
    };
    StatePacketSpeaker(int _car, int _id, std::string _mode, StatePacketType _type){
        id = _id;
        mode = _mode;
        switch(_type){
        case NORMAL:
            cacc_state_packet_pub = nh.advertise<cacc_msgs::CaccStatePacket>(mode+"_Car_"+std::to_string(_car)+"/state_packet", 1);
            break;
        case ERROR:
            cacc_state_packet_pub = nh.advertise<cacc_msgs::CaccStatePacket>(mode+"_Car_"+std::to_string(_car)+"/error_packet", 1);
            break;
        case CURRENT:
            cacc_state_packet_pub = nh.advertise<cacc_msgs::CaccStatePacket>(mode+"_Car_"+std::to_string(_car)+"/curr_state_packet", 1);
            break;
        case PREDICT:
            cacc_state_packet_pub = nh.advertise<cacc_msgs::CaccStatePacket>(mode+"_Car_"+std::to_string(_car)+"/predicted_state_packet", 1);
            break;
        }
    };
    void publish_cacc_state_packet_msg(const cacc_msgs::CaccStatePacket& msg){
        cacc_state_packet_msg = msg;
        if(cacc_state_packet_msg.id != id){
            ROS_ERROR("Incorrect ID on state packet has been set to StatePacketSpeaker. ID of the message is not matched to the speaker ID. (speaker: %d, msg: %d)", id, cacc_state_packet_msg.id);
            ROS_ERROR("Trying to write followings:\nid: %d\nmanual: %d\nactivated: %d\nthw: %f\ndistance: %f\nspeed: %f\nacceleration: %f", cacc_state_packet_msg.id, cacc_state_packet_msg.manual, cacc_state_packet_msg.activated, cacc_state_packet_msg.thw, cacc_state_packet_msg.distance, cacc_state_packet_msg.speed, cacc_state_packet_msg.acceleration);
        }
        else{
            cacc_state_packet_pub.publish(cacc_state_packet_msg);
        }
    }
};

class StatePacketListener{
private:
    ros::Subscriber cacc_state_packet_sub;
    cacc_msgs::CaccStatePacket cacc_state_packet_msg;
    void caccStatePacketCallback(const cacc_msgs::CaccStatePacket& msg){
        cacc_state_packet_msg = msg;
        //ROS_INFO("StatePacketListener: GETTING MSG (listener: %d, msg: %d)", id, msg.id);
    };

public:
    ros::NodeHandle nh;
    int id;
    std::string mode;
    StatePacketListener(int _car, int _id, std::string _mode){
        id = _id;
        mode = _mode;
        cacc_state_packet_sub = nh.subscribe(mode+"_Car_"+std::to_string(_car)+"/state_packet", 5, &StatePacketListener::caccStatePacketCallback, this);
    };
    StatePacketListener(int _car, int _id, std::string _mode, std::string _topic){
        id = _id;
        mode = _mode;
        cacc_state_packet_sub = nh.subscribe(_topic, 5, &StatePacketListener::caccStatePacketCallback, this);
    };
    void get_cacc_state_packet_msg(cacc_msgs::CaccStatePacket* msg){
        *msg = cacc_state_packet_msg;
    }
};

#endif