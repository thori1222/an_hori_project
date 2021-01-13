#include <Car.h>

#include <ros/ros.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
//#include <tf/Matrix3x3>
#include <custom_pkg/control_signal.h>

#include <iostream>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>

#define RAD2DEG 180.0/M_PI
#define SPEED_PWM_MAX 50
#define Y_OFFSET_LIM 0.5

RCcar* car;

std::string control_cmd_topic;
std::string current_pose_topic;
std::string motor_signal_topic;

std::string course_frame;
std::string car_frame;

double initial_x = 1.5;
double initial_y = 5.0;
double initial_yaw = 0.0;

double dt = 0.01;

void controlSignalCallback(const custom_pkg::control_signal::ConstPtr& msg)
{
    car->setMotor(msg->accel);
    car->setServo(msg->steer);
    car->updateControlInput();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "car_simulator");

    ros::NodeHandle n,pn("~");

    pn.param<std::string>("current_pose_topic", current_pose_topic, "/vrpn_client_node/RigidBody/pose");
    pn.param<std::string>("control_cmd_topic", control_cmd_topic, "/control_signal");
    pn.param<std::string>("motor_signal_topic", motor_signal_topic, "/motor_signal");
    pn.param<std::string>("course_frame", course_frame, "course");
    pn.param<std::string>("car_frame", car_frame, "car");
    pn.param<double>("initial_x", initial_x, 1.5);
    pn.param<double>("initial_y", initial_y, 5.0);
    pn.param<double>("initial_yaw", initial_yaw, 0.0);
    
    ros::Subscriber controlSignalSub = n.subscribe(control_cmd_topic, 10, controlSignalCallback);
    ros::Publisher currentPosePub = n.advertise<geometry_msgs::PoseStamped>(current_pose_topic, 1);
    ros::Publisher motorSignalPub = n.advertise<custom_pkg::control_signal>(motor_signal_topic, 1);
    tf::TransformBroadcaster tfBroadcaster;

    if(car != NULL){
        delete car;
        car = NULL;
    };
    car = new RCcar();
    car->setX(initial_x);
    car->setY(initial_y);
    car->setYaw(initial_yaw);

    ros::Rate loop_rate(1.0/dt);	// 100 Hz

    // START LOOOOOOOOOOOOP!
    while(ros::ok()) {
        ros::spinOnce();

        // Update the car state
        car->updateSteer(dt);
        car->update(dt);
        
        // printf("=========================\n");
        // printf("Current state: \n");
        // printf("Vel: %f, \nSteer: %f \nX: %f, \nY: %f, \nYaw: %f\n", 
        //         car->getV(), car->getSteer(), car->getX(), car->getY(), car->getYaw());
        // printf("=========================\n");

        // Pack the state to the msgs
        geometry_msgs::PoseStamped pose_msg;
        geometry_msgs::TransformStamped pose_tf;
        custom_pkg::control_signal motor_signal_msg;

        pose_tf.header.stamp = ros::Time::now();
        pose_tf.header.frame_id = course_frame;
        pose_tf.child_frame_id = car_frame;

        geometry_msgs::Quaternion pose_quat = tf::createQuaternionMsgFromYaw(car->getYaw()-M_PI/2);

        pose_tf.transform.translation.x = car->getX();
        pose_tf.transform.translation.y = car->getY();
        pose_tf.transform.translation.z = 0.0;
        pose_tf.transform.rotation = pose_quat;
        
        tfBroadcaster.sendTransform(pose_tf);

        pose_msg.header.stamp = ros::Time::now();
        pose_msg.header.frame_id = course_frame;

        //set the position
        pose_msg.pose.position.x = car->getX();
        pose_msg.pose.position.y = car->getY();
        pose_msg.pose.position.z = 0.0;
        pose_msg.pose.orientation = pose_quat;

        motor_signal_msg.status = 1;
        motor_signal_msg.accel = car->getMotor();
        motor_signal_msg.steer = car->getServo();

        //publish the message
        currentPosePub.publish(pose_msg);
        motorSignalPub.publish(motor_signal_msg);

        loop_rate.sleep();
    }

    delete car;
    return 0;
}
