#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>

#include <geometry_msgs/PoseStamped.h>

#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#define DEBUG
#define USE_ROS_LAUNCH

int main(int argc, char **argv){
    ros::init(argc, argv, "rosbag_player");

std::string filename;
std::string topic_to_read;
std::string topic_to_publish;
int period = 100;

#ifdef USE_ROS_LAUNCH
    ros::NodeHandle private_nh("~");
    private_nh.param<std::string>("filename", filename, "/tmp/file.bag");
    private_nh.param<std::string>("topic_to_read", topic_to_read, "/pose");
    private_nh.param<std::string>("topic_to_publish", topic_to_publish, "/pose_repub"); 
    private_nh.param<int>("period", period, 100);    

#else
    if(argc != 5 || argc != 4){
        ROS_ERROR("Wrong input variables. ./rosbag_player file.bag /topic_to_read /topic_to_publish period");
        return -1;
    }

    filename = argv[1];
    topic_to_read = argv[2];
    topic_to_publish = argv[3];
    if(argc == 5) period = argv[4];
#endif
    
    ros::NodeHandle nh;
    ros::Publisher pose_pub = nh.advertise<geometry_msgs::PoseStamped>(topic_to_publish, 5);
    
    rosbag::Bag bag;
    bag.open(filename, rosbag::bagmode::Read);
    rosbag::View view(bag, rosbag::TopicQuery(topic_to_read));
    std::vector<geometry_msgs::PoseStamped> pose_vector;

#ifdef DEBUG
    ROS_INFO("Start to read the rosbag file.");
#endif
    foreach(rosbag::MessageInstance const m, view){
        geometry_msgs::PoseStamped::ConstPtr p = m.instantiate<geometry_msgs::PoseStamped>();
        if(p != NULL){
            pose_vector.push_back(*p);
        }
	else{
#ifdef DEBUG
    ROS_INFO("No topic msgs named %s.", topic_to_read.c_str());
#endif	    
	}
    }
    bag.close();
    int cnt_max = pose_vector.size();

#ifdef DEBUG
    ROS_INFO("Loading bag file completed!...%d", cnt_max);
    ROS_INFO("Loop start!");
#endif

    int cnt = 0;
    ros::Rate loop_rate(period);
    while (ros::ok()){
        geometry_msgs::PoseStamped msg;

        msg.header.stamp = ros::Time::now();
        msg.pose = pose_vector[cnt].pose;

#ifdef DEBUG
    ROS_INFO("===========================");
    ROS_INFO("Publishing %d-th msg", cnt);
    ROS_INFO("x: %f, y: %f", msg.pose.position.x, msg.pose.position.y);
#endif
	
        pose_pub.publish(msg);

        if(cnt++ == cnt_max){
            cnt = 0;
        };

	loop_rate.sleep();
    }
    return 0;
}
