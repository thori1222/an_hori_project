#include <car_communicator.h>

namespace Udp_ns{
    
CarSender::CarSender(std::string _destination, unsigned short _port):private_nh("~"),UdpSender(_destination, _port){
    private_nh.param<int>("id", id, 1101);
    private_nh.param<bool>("manual", manual, false);
    private_nh.param<float>("thw", thw, 2.0);
    private_nh.param<float>("sensor2frontbumper", sensor2frontbumper, 3.0);
    private_nh.param<float>("sensor2rearbumper", sensor2rearbumper, 3.0);
    private_nh.param<std::string>("radar_topic", radar_str, "/min_radar");
    private_nh.param<std::string>("curr_pose_topic", curr_pose_str, "/curr_pose");
    private_nh.param<std::string>("curr_twist_topic", curr_twist_str, "/curr_twist");
    private_nh.param<std::string>("twist_type", twist_type_str, "TwistStamped");

    if(twist_type_str == "TwistStamped")
        twist_type = TWIST_STAMPED;
    else if(twist_type_str == "TwistWithCovarianceStamped")
        twist_type = TWIST_WITH_COVARIANCE_STAMPED;
    else
        ROS_ERROR("Wrong twist type has been set.");
	
    //Setting for ROS
    cacc_sensor_packet_msg.id = id;
    cacc_sensor_packet_msg.manual = manual;
    cacc_sensor_packet_msg.thw = thw;
    cacc_sensor_packet_msg.alpha = 10;
    cacc_sensor_packet_msg.beta = 10;
    cacc_sensor_packet_msg.sensor2frontbumper = sensor2frontbumper;
    cacc_sensor_packet_msg.sensor2rearbumper = sensor2rearbumper;
    cacc_sensor_packet_msg.vel_gain = 10;
    cacc_sensor_packet_msg.vel_gain_low = 50;
    cacc_sensor_packet_msg.vel_gain_dec = 100;
    
    radar_sub = nh.subscribe(radar_str,1,&Udp_ns::CarSender::radarCallback, this);
    curr_pose_sub = nh.subscribe(curr_pose_str,1,&Udp_ns::CarSender::currPoseCallback, this);
    switch(twist_type){
    case TWIST_STAMPED:
    	curr_twist_sub = nh.subscribe(curr_twist_str,1,&Udp_ns::CarSender::currTwistCallback,this);
        break;
    case TWIST_WITH_COVARIANCE_STAMPED:
    	curr_twist_sub = nh.subscribe(curr_twist_str,1,&Udp_ns::CarSender::currTwistWithCovarianceCallback,this);
        break;
    }
    cacc_sensor_packet_pub = nh.advertise<cacc_msgs::CaccSensorPacket>("cacc_sensor_packet", 1);
    
    f = boost::bind(&Udp_ns::CarSender::carParamConfigCallback, this, _1, _2);
    server.setCallback(f);

    checksum = 0;
};
    
CarSender::~CarSender(){
    close(socket_var);
};

void CarSender::radarCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
    cacc_sensor_packet_msg.front_distance = 0.95*cacc_sensor_packet_msg.front_distance + 0.05*msg->pose.position.x;
};

void CarSender::currPoseCallback(const geometry_msgs::PoseStamped::ConstPtr& msg){
    tf::Quaternion q(
        msg->pose.orientation.x,
        msg->pose.orientation.y,
        msg->pose.orientation.z,
        msg->pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);

    cacc_sensor_packet_msg.x = msg->pose.position.x;
    cacc_sensor_packet_msg.y = msg->pose.position.y;
    cacc_sensor_packet_msg.yaw = yaw;
};
   
void CarSender::currTwistCallback(const geometry_msgs::TwistStamped::ConstPtr& msg){
    t_now = ros::Time::now();
    time_diff = t_now - t_prev;
    dt = time_diff.toSec();
    if(dt >= 0.005){
        double tmp_speed = 0.5*cacc_sensor_packet_msg.speed + 0.5*sqrt(msg->twist.linear.x*msg->twist.linear.x + msg->twist.linear.y*msg->twist.linear.y);
        double tmp_acceleration = (tmp_speed - cacc_sensor_packet_msg.speed)/dt;
        cacc_sensor_packet_msg.speed = tmp_speed;
        cacc_sensor_packet_msg.acceleration = 0.95*cacc_sensor_packet_msg.acceleration + 0.05*tmp_acceleration;
    }
    t_prev = t_now;
};

void CarSender::currTwistWithCovarianceCallback(const geometry_msgs::TwistWithCovarianceStamped::ConstPtr& msg){
    t_now = ros::Time::now();
    time_diff = t_now - t_prev;
    dt = time_diff.toSec();
    if(dt >= 0.005){
        double tmp_speed = 0.5*cacc_sensor_packet_msg.speed + 0.5*sqrt(msg->twist.twist.linear.x*msg->twist.twist.linear.x + msg->twist.twist.linear.y*msg->twist.twist.linear.y);    
        double tmp_acceleration = (tmp_speed - cacc_sensor_packet_msg.speed)/dt;
        cacc_sensor_packet_msg.speed = tmp_speed;
        cacc_sensor_packet_msg.acceleration = 0.95*cacc_sensor_packet_msg.acceleration + 0.05*tmp_acceleration;
    }
    t_prev = t_now;
};
        
    
void CarSender::caccSensorPacketSend(const cacc_msgs::CaccSensorPacket& msg){
    int packet_length = sizeof(msg);
    if( sendto(socket_var, &msg, packet_length, 0, (const sockaddr*)&sock_addr, sizeof(sock_addr)) < 0 )
    {
      ROS_ERROR("Cannot send command from CarSender" );
    }

    cacc_sensor_packet_pub.publish(msg);
};

void CarSender::carParamConfigCallback(cacc_communicator::carParamConfig &config, uint32_t level){
    thw = config.thw;
    tau = config.tau;
    K = config.K;
    // tau[0] = config.tau_acc0;
    // K[0] = config.K_acc0;
    // tau[1] = config.tau_acc10;
    // K[1] = config.K_acc10;
    // tau[2] = config.tau_dec10;
    // K[2] = config.K_dec10;
    // tau[3] = config.tau_dec20;
    // K[3] = config.K_dec20;
    vel_gain = config.vel_gain;
    vel_gain_low = config.vel_gain_low;
    vel_gain_dec = config.vel_gain_dec;
};
    
void CarSender::run(){
    ros::Rate loop_rate(100);
    while(ros::ok()){
        ros::spinOnce();
        
        // Dummy data for front & rear detection
        //cacc_sensor_packet_msg.speed = 10.0;
        //cacc_sensor_packet_msg.rear_speed = 10.0;
        //cacc_sensor_packet_msg.front_speed = 10.0;
        //cacc_sensor_packet_msg.front_distance = -sensor2frontbumper + 5.0 + cacc_sensor_packet_msg.speed * thw;
        //cacc_sensor_packet_msg.rear_distance = -sensor2frontbumper + 5.0 + cacc_sensor_packet_msg.speed * thw;
        
        cacc_sensor_packet_msg.thw = thw;
        //cacc_sensor_packet_msg.alpha = alpha;
        cacc_sensor_packet_msg.alpha = 1/tau;
        cacc_sensor_packet_msg.beta = K/tau;
        // if(cacc_sensor_packet_msg.acceleration > 0){
        //     if(cacc_sensor_packet_msg.speed > 10*1.6/3.6){ //acc_10mph
        //         cacc_sensor_packet_msg.alpha = 1/tau[1];
        //         cacc_sensor_packet_msg.beta = K[1]/tau[1];
        //     }
        //     else //acc_0mph
        //     {
        //         cacc_sensor_packet_msg.alpha = 1/tau[0];
        //         cacc_sensor_packet_msg.beta = K[0]/tau[0];
        //     }
        // }
        // else{
        //     if(cacc_sensor_packet_msg.speed > 20*1.6/3.6){ //dec_20mph
        //         cacc_sensor_packet_msg.alpha = 1/tau[3];
        //         cacc_sensor_packet_msg.beta = K[3]/tau[3];
        //     }
        //     else //dec_10mph
        //     {
        //         cacc_sensor_packet_msg.alpha = 1/tau[2];
        //         cacc_sensor_packet_msg.beta = K[2]/tau[2];
        //     }
        // }
        
        cacc_sensor_packet_msg.vel_gain = vel_gain;
        cacc_sensor_packet_msg.vel_gain_low = vel_gain_low;
        cacc_sensor_packet_msg.vel_gain_dec = vel_gain_dec;
        cacc_sensor_packet_msg.checksum = checksum;
        
        caccSensorPacketSend(cacc_sensor_packet_msg);

        checksum++;
        
        loop_rate.sleep();
    }
};

};

int main(int argc, char** argv){
    ros::init(argc, argv, "car_sender");
    
    std::string destination;
    int port;

    ros::NodeHandle private_nh("~");

    private_nh.param<std::string>("destination", destination, "192.168.13.52");
    private_nh.param<int>("port_send", port, 54650);

    Udp_ns::CarSender car_sender(destination, port);
    car_sender.run();    
    
    return 0;
}
