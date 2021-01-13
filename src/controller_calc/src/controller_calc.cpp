#include "math.h"
#include "ros/ros.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "geometry_msgs/TwistStamped.h"
#include "tf/transform_datatypes.h"
//#include <tf/Matrix3x3>
#include "sensor_msgs/Imu.h"
//#include "wiringPi.h"
#include "iostream"

#include <string>
#include <std_msgs/Float32MultiArray.h>
#include <custom_pkg/control_signal.h>
#include "FrenetCoordinate.h"
#include "Car.h"
#include "Car_control.h"
#include "nav_msgs/Path.h"
#include <iostream>
#include <fstream>

#define RAD2DEG 180.0/M_PI
#define SPEED_PWM_MAX 50
#define Y_OFFSET_LIM 0.5

using namespace std;
using namespace RTCLib;
using namespace Eigen;
/**
 * Obtain the IMU data from the topic /imu/data
 * and the pose data from the topic /vrpn_client_node/Robot_1/pose
 *
 * Convert the ROS frame to Object frame/IMU frame!
 * Created by: TRAN Anh Tuan 2019/09/06
 */

float gyro_x, gyro_y, gyro_z;
float acc_x, acc_y, acc_z;
float angle_x, angle_y, angle_z;

float angle_Optitrack_x, angle_Optitrack_y, angle_Optitrack_z;
float pos_x, pos_y, pos_z;
float pos_x_cutin, pos_y_cutin, pos_z_cutin;


double time_OptiTrack_current, time_OptiTrack_last;

int Flag_motor_start = 0;
bool Flag_control_start = true;
bool Flag_csv_output = true;
bool Flag_speed_ref_update = false;
bool Flag_y_shift = false;
bool Flag_cutin = false;

std::string imu_topic, current_pose_topic, current_pose_topic_cutin, motor_signal_topic;
std::string control_cmd_topic, filtered_imu_topic, speed_ref_topic, speed_ref_topic_2, curr_speed_topic;
std::string path_ref_topic, path_car_topic;
std::string path_file, path_to_write_path, output_lane_for_debug, output_csv_folder;

double speed_ref;
double y_offset = 0.0;
double THW;

int speed_mode = 0;  //0: normal, 1:sin curve, 2: slow and fast
int speed_counter = 0;
double speed_ref_ref = 0.5;

//for cutin
int cut_in = 1;
int cut_in_mode = 0;
double t_cutin = 0.0;



/* =====================================================================
 * Receive data from IMU topic
 * =====================================================================
 */
void chatterCallback_IMU(const sensor_msgs::Imu::ConstPtr& msg)
{
    gyro_x = msg->angular_velocity.x;
    gyro_y = msg->angular_velocity.y;	// Convert ROS frame to IMU frame
    gyro_z = msg->angular_velocity.z;	// Convert ROS frame to IMU frame

    acc_x = msg->linear_acceleration.x;
    acc_y = msg->linear_acceleration.y;	// Convert ROS frame to IMU frame
    acc_z = msg->linear_acceleration.z;	// Convert ROS frame to IMU frame

    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg->orientation,quat);

    double roll, pitch, yaw;

    tf::Matrix3x3(quat).getRPY(roll,pitch,yaw);

    angle_y = roll;
    angle_x =-pitch;		// Convert ROS-frame to IMU-frame
    angle_z = yaw;  		// Convert ROS-frame to IMU-frame
    
    //fprintf(stdout,"Gyroscope X = %.2f, Gyroscope Y = %.2f, Gyroscope Z = %.2f \n", gyro_x, gyro_y, gyro_z);
    //fprintf(stdout,"Acceleration X = %.2f, Acceleration Y = %.2f, Acceleration Z = %.2f \n", acc_x, acc_y, acc_z);
    //fprintf(stdout,"Angle X = %.2f, Angle Y = %.2f, Angle Z = %.2f \n", angle_x, angle_y, angle_z);
    
}


/* =====================================================================
 * Receive data from Motion Capture topic
 * =====================================================================
 */
void chatterCallback_Optitrack(const geometry_msgs::PoseStamped::ConstPtr& msg)
{

    time_OptiTrack_current = msg->header.stamp.sec+msg->header.stamp.nsec*1e-9;
    //fprintf(stdout,"time = %f\n",time_OptiTrack_current);

    pos_x = msg->pose.position.x;
    pos_y = msg->pose.position.y;	// Convert ROS frame to IMU frame
    pos_z = msg->pose.position.z;	// Convert ROS frame to IMU frame

    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg->pose.orientation,quat);

    double roll_opti, pitch_opti, yaw_opti;

    tf::Matrix3x3(quat).getRPY(roll_opti,pitch_opti,yaw_opti);

    angle_Optitrack_x = roll_opti;		// In Ground Coordinate system
    angle_Optitrack_y = pitch_opti;		// In Ground Coordinate system
    angle_Optitrack_z = yaw_opti;  		// In Ground Coordinate system

    /*
    fprintf(stdout,"Pos. X = %.2f, Pos. Y = %.2f, Pos. Z = %.2f \n", pos_x, pos_y, pos_z);
    fprintf(stdout,"Angle (Opti) X = %.2f, Angle (Opti) Y = %.2f, Angle (Opti) Z = %.2f \n", angle_Optitrack_x, angle_Optitrack_y, angle_Optitrack_z);
    */
}

void chatterCallback_Optitrack_cutin(const geometry_msgs::PoseStamped::ConstPtr& msg)
{
    if(Flag_cutin)
    {
        pos_x_cutin = msg->pose.position.x;
        pos_y_cutin = msg->pose.position.y;	
        pos_z_cutin = msg->pose.position.z;	
    }
}

void chatterCallback_MotorSignal(const custom_pkg::control_signal::ConstPtr& msg)
{
    Flag_motor_start = msg->status;

}

void chatterCallback_SpeedRef(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    if(Flag_speed_ref_update){
        if (cut_in == 1)
	    speed_ref = msg->twist.linear.x;
    }
}

void chatterCallback_SpeedRef_2(const geometry_msgs::TwistStamped::ConstPtr& msg)
{
    if(Flag_speed_ref_update){
        if (cut_in == 0)
	    speed_ref = msg->twist.linear.x;
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "imu_receive");

    ros::NodeHandle n,pn("~");

    pn.param<std::string>("imu_topic", imu_topic, "/imu/data");
    pn.param<std::string>("current_pose_topic", current_pose_topic, "/vrpn_client_node/RigidBody/pose");
    pn.param<std::string>("current_pose_topic_cutin", current_pose_topic_cutin, "/vrpn_client_node/RigidBody/pose");
    pn.param<std::string>("motor_signal_topic", motor_signal_topic, "/motor_signal");
    pn.param<std::string>("control_cmd_topic", control_cmd_topic, "/control_signal");
    pn.param<std::string>("filtered_imu_topic", filtered_imu_topic, "/imu/data_filtered");
    pn.param<std::string>("curr_speed_topic", curr_speed_topic, "/curr_speed");
    pn.param<std::string>("speed_ref_topic", speed_ref_topic, "/speed_ref");
    pn.param<std::string>("speed_ref_topic_2", speed_ref_topic_2, "/speed_ref");
    pn.param<std::string>("path_ref_topic", path_ref_topic, "/path_ref");
    pn.param<std::string>("path_car_topic", path_car_topic, "/path_car");
    pn.param<std::string>("path_file", path_file, "src/controller_calc/Path_Info/path.csv");
    pn.param<std::string>("path_to_write_path", path_to_write_path, "src/controller_calc/Path_Info/resampled_path.csv");
    pn.param<std::string>("output_lane_for_debug", output_lane_for_debug, "src/controller_calc/Path_Info/output_lane.csv");
    pn.param<std::string>("output_csv_folder", output_csv_folder, "data_exp");
    pn.param<bool>("Flag_csv_output", Flag_csv_output, true);
    pn.param<bool>("Flag_control_start", Flag_control_start, true);
    pn.param<bool>("Flag_speed_ref_update", Flag_speed_ref_update, false); 
    pn.param<bool>("Flag_y_shift", Flag_y_shift, true);
    pn.param<bool>("Flag_cutin", Flag_cutin, false); 
    pn.param<double>("speed_ref", speed_ref, 1.5);
    pn.param<double>("y_offset", y_offset, 0.0);
    pn.param<double>("THW", THW, 0.2);
    pn.param<int>("speed_mode", speed_mode, 0);

    ros::Subscriber sub = n.subscribe(imu_topic, 1000, chatterCallback_IMU);
    ros::Subscriber sub1 = n.subscribe(current_pose_topic, 1000, chatterCallback_Optitrack);
    ros::Subscriber sub2 = n.subscribe(current_pose_topic_cutin, 1000, chatterCallback_Optitrack_cutin);
    ros::Subscriber sub3 = n.subscribe(motor_signal_topic, 1000, chatterCallback_MotorSignal);
    ros::Subscriber sub4 = n.subscribe(speed_ref_topic, 5, chatterCallback_SpeedRef);
    ros::Subscriber sub5 = n.subscribe(speed_ref_topic_2, 5, chatterCallback_SpeedRef_2);

    ros::Publisher pub = n.advertise<custom_pkg::control_signal>(control_cmd_topic, 50);
	ros::Publisher pub1 = n.advertise<sensor_msgs::Imu>(filtered_imu_topic, 50);
	ros::Publisher pub2 = n.advertise<geometry_msgs::TwistStamped>(curr_speed_topic, 1);
    
    // Declaration for publishing the reference path
    // of "nav_msgs::path" type

    ros::Publisher pub_path = n.advertise<nav_msgs::Path>(path_ref_topic,50);
    nav_msgs::Path path_ref;
    geometry_msgs::PoseStamped pose_ref;
    std::vector<geometry_msgs::PoseStamped> pose_vec_ref;

    // Declaration for publishing the car's path
    // of "nav_msgs::path" type
    ros::Publisher pub_path_car = n.advertise<nav_msgs::Path>(path_car_topic,50);
    nav_msgs::Path path_car;
    geometry_msgs::PoseStamped pose_car;

    ros::Rate loop_rate(100);	// 100 Hz

    custom_pkg::control_signal dat;
	sensor_msgs::Imu imu_filtered;
    Car car;

    double steer_pwm_cmd = 0.0;
    double speed_pwm_cmd = 0.0;
    double current_speed = 0.0;
    double dt = 0.01; 					//initial sampling time
    double time_ros_current, time_ros_last=-1;
    ros::Duration(3).sleep();

    FrenetCoordinate2D lane_center;

    lane_center.LoadPathFromCSV(path_file, true);
    lane_center = lane_center.ResampleConservative(0.01);
    lane_center.WritePath(ofstream(path_to_write_path));
    lane_center.OutputLaneForDebug(output_lane_for_debug);
    
    static CacheToFrenet cache_to_g;
    double lane_u = 0;
    double lane_v = 0;
    double theta_d_lane = 0;
    double theta_e_lane = 0;

    double u, y_e, y_e_dot, theta_e, theta_e_dot;

    double Tf = 0.2;	// Derivative filter's time constant
    StateFBControlParameter ssbParam;

    string ControlMethod = "StateFB";

    ros::WallTime time_check_start, time_check_end;
    double time_check_calc;

    // Save the path data to path_ref
    for (size_t i = 0; i < lane_center.size; i++) {
        pose_ref.pose.position.x = lane_center.points[i].pos.x();
        pose_ref.pose.position.y = lane_center.points[i].pos.y();
        pose_ref.pose.position.z = 0; // Set z = 0;
        pose_ref.pose.orientation.x = 0.0;
        pose_ref.pose.orientation.y = 0.0;
        pose_ref.pose.orientation.z = 0.0;
        pose_ref.pose.orientation.w = 1.0;
        path_ref.poses.push_back(pose_ref);
    }

    path_ref.header.stamp = ros::Time::now();
    path_ref.header.frame_id = "course"; 	// Need to set the frame id

    // Open CSV file
    std::ofstream myfile;
    time_t now = time(NULL);
    tm* now_local = localtime(&now);

    if(Flag_csv_output){
        char str[256];
        strftime(str,sizeof(str)-1,"%Y%m%d_%H%M%S",now_local);    
        string date_str(str);
        //string filename = "/home/chinhyuntai/data_exp/data_exp_" + date_str + ".csv";
        string filename = output_csv_folder + "/data_exp_" + date_str + ".csv";
        myfile.open (filename);
        // myfile << "Time,px,py,pz,vx,vy,u,y_e,theta_e,theta_d_lane,ahead_theta_d,y_e_dot,theta_e_dot,delta_theta_d_lane,speed_pwm_cmd,steer_pwm_cmd,gyro_x,gyro_y,gyro_z,acc_x,acc_y,acc_z,angle_x,angle_y,angle_z,angle_Optitrack_x,angle_Optitrack_y,angle_Optitrack_z\n";
        // myfile << "Time,px,py,pz,vx,vy,v,speed_ref,u,y_e,theta_e,theta_d_lane,ahead_theta_d,y_e_dot,theta_e_dot,delta_theta_d_lane,speed_pwm_cmd,steer_pwm_cmd\n";
        myfile << "Time,v,u\n";
    }

    double time_exp_start;
    time_exp_start = ros::Time::now().toSec();

	double vx, vy, vz;
	double px, py, pz, car_yaw;
	double angle_Opt_x,angle_Opt_y,angle_Opt_z;
	
	LowPassFilter data_gyroX, data_gyroY, data_gyroZ, data_accX, data_accY, data_accZ;
	data_accZ.set_init(-9.81);		// initial guess of accZ
		
	double gyroX_filtered, gyroY_filtered, gyroZ_filtered, accX_filtered, accY_filtered, accZ_filtered;
	double x_vx = 0, x_vy = 0, x_vz = 0;
    double x_PID_speed = 0;
	PID speed_PIDcontrol(30,0,0,30,-30);		// (Kp, Ki, Kd, error_integration_max, error_integration_min)

    double D_theta_e_temp = 0;
	double D_ye_temp = 0;


    // START LOOOOOOOOOOOOP!
    while(ros::ok()) {
        pn.getParam("Flag_control_start", Flag_control_start);
		pn.getParam("Flag_csv_output", Flag_csv_output);
		pn.getParam("Flag_speed_ref_update", Flag_speed_ref_update);
		pn.getParam("Flag_y_shift", Flag_y_shift);
        if(!Flag_speed_ref_update)
    		pn.getParam("speed_ref", speed_ref);
		pn.getParam("THW", THW);
		if(Flag_y_shift)
            pn.getParam("y_offset", y_offset);

		// Use a low-pass filter to filter IMU data
		data_gyroX.set_input(gyro_x);	data_gyroX.calculate();		gyroX_filtered = data_gyroX.get_output();
		data_gyroY.set_input(gyro_y);	data_gyroY.calculate();		gyroY_filtered = data_gyroY.get_output();
		data_gyroZ.set_input(gyro_z);	data_gyroZ.calculate();		gyroZ_filtered = data_gyroZ.get_output();
		
		data_accX.set_input(acc_x); 	data_accX.calculate();		accX_filtered = data_accX.get_output();
		data_accY.set_input(acc_y);		data_accY.calculate();		accY_filtered = data_accY.get_output();
		data_accZ.set_input(acc_z);		data_accZ.calculate();		accZ_filtered = data_accZ.get_output();
				
		// Save the current data from OptiTrack
		angle_Opt_x = angle_Optitrack_x;	angle_Opt_y = angle_Optitrack_y;	angle_Opt_z = angle_Optitrack_z;
        
        time_ros_current = ros::Time::now().toSec();
        // Calculate the sampling time
        if (time_ros_last ==-1) {
            dt = 0.01;
        }
        else {
            dt = time_ros_current - time_ros_last;
        }
        time_check_start = ros::WallTime::now();

        // Calculate velocity
        // Note that the update frequency of pos_x, pos_y (which will be updated every time the motion capture system sends a new message)
        // and the update frequency of car.setX, car.setY, etc. (which is determined by the ros::rate) are different
        car.setX(pos_x);
        car.setY(pos_y);
        car.setZ(pos_z);
        car.setYaw(angle_Optitrack_z);
        px = car.getX();
        py = car.getY();
        pz = car.getZ();
        car_yaw = car.getYaw();
        
        DerivativeFilter car_vx(px, 0.1, dt);	// the second arg: Derivative Filter's time constant Ts
        car_vx.calculate(x_vx);        
        car.setVx(car_vx.get_output());
       
        DerivativeFilter car_vy(py, 0.1, dt);	// the second arg: Derivative Filter's time constant Ts
        car_vy.calculate(x_vy);        
        car.setVy(car_vy.get_output());

        DerivativeFilter car_vz(pz, 0.1, dt);	// the second arg: Derivative Filter's time constant Ts
        car_vz.calculate(x_vz);        
        car.setVz(car_vz.get_output());
                
        //velocity_OptiTrack_simple(car,dt);
        //car.print();		// Print position and velocity of the car
        vx = car.getVx();
        vy = car.getVy();
        vz = car.getVz();
        current_speed = sqrt(vx*vx+vy*vy+vz*vz);
        
        geometry_msgs::TwistStamped curr_speed;
        curr_speed.header.stamp = ros::Time::now();
        curr_speed.twist.linear.x = vx;
        curr_speed.twist.linear.y = vy;
        curr_speed.twist.linear.z = vz;
        
        pub2.publish(curr_speed);
        
        //fprintf(stdout,"(px,py,vx,vy) = (%.2f,%.2f,%.2f,%.2f)\n", px, py, vx, vy);

        // OptiTrack calculates the yaw angle w.r.t. y-axis
        // while the code below considers the yaw angle w.r.t. x-xis
        // => Compensate an amount of PI/2
        cache_to_g = lane_center.GetFrenet(pos_x, pos_y, angle_Optitrack_z+M_PI/2, lane_u, lane_v, theta_e_lane, cache_to_g);

        FrenetPoint2D lc_point = lane_center.GetPoint(cache_to_g);
        theta_d_lane = lc_point.to_next_theta;

        u = lane_u;
        y_e = lane_v;
        if(Flag_y_shift){
            if(y_offset > Y_OFFSET_LIM){
                ROS_WARN("y_offset is out of the limit!");
                y_offset = Y_OFFSET_LIM;
            }
            else if(y_offset < -Y_OFFSET_LIM){
                ROS_WARN("y_offset is out of the limit!");
                y_offset = -Y_OFFSET_LIM;
            }
            y_e += y_offset;
        }
        theta_e = theta_e_lane;

        // Calculate theta_e_dot and y_e_dot using derivative filter with
        // with the filter's time constant of Tf
        DerivativeFilter D_theta_e(theta_e,0.1,dt);
        D_theta_e.calculate(D_theta_e_temp);
        theta_e_dot = D_theta_e.get_output();
        
        DerivativeFilter D_ye(y_e,0.1,dt);
        D_ye.calculate(D_ye_temp);
        y_e_dot = D_ye.get_output();
        
        // Look Ahead for Feedforward
        // Look ahead in TWH seconds, calculate the error of the "ahead_theta_d" of the path and the current "theta_d"
        // and feedforward that amount to the steer angle

        //double ahead_len = ssbParam.SFBLLook;
        double ahead_len = current_speed*THW;
        if (ahead_len<0) {
            ahead_len = -ahead_len;
        };

        double ahead_x = px + ahead_len * cos(car_yaw);
        double ahead_y = py + ahead_len * sin(car_yaw);
        double ahead_theta_e = 0.0;
        double ahead_theta_d = 0.0;

        static CacheToFrenet cache_to_g_ahead;
        cache_to_g_ahead = lane_center.GetFrenet(ahead_x, ahead_y, car.getYaw(),lane_u, lane_v, ahead_theta_e, cache_to_g_ahead);
        FrenetPoint2D lc_point_ahead = lane_center.GetPoint(cache_to_g_ahead);
        ahead_theta_d = lc_point_ahead.to_next_theta;

        double delta_theta_d_lane = mod(ahead_theta_d - theta_d_lane, M_PI); 	// if the error is larger than PI, take the modulus

        //double delta_theta_d_lane = (ahead_theta_d - theta_d_lane);
        //fprintf(stdout,"u=%.2f, y_e=%.2f, theta_e=%.2f, theta_d=%.2f,theta_e_dot=%.2f, y_e_dot=%.2f, delta_theta_d = %.5f\n", u, y_e, theta_e, theta_d_lane, theta_e_dot, y_e_dot,delta_theta_d_lane);
        //fprintf(stdout,"Motor start = %.1f\n",Flag_motor_start);

        if (ControlMethod == "StateFB")
        {
            // State vector
            double state[4];
            state[0] = y_e;
            state[1] = y_e_dot;
            state[2] = theta_e;
            state[3] = theta_e_dot;
            // steering angle
            steer_pwm_cmd =
                + state[0] * ssbParam.SFBK1
                + state[1] * ssbParam.SFBK2
                + state[2] * ssbParam.SFBK3
                + state[3] * ssbParam.SFBK4
                + 500 * delta_theta_d_lane;
        }
        
        // if (speed_mode == 1)  //sincurve,  range: 0.8~1.3
        // {
        //     if (speed_counter ==0)
        //     {
        //         speed_ref_ref = 0;
        //         speed_counter = 1;
        //     }

        //     speed_ref = 1.05 - 0.25*sin(speed_ref_ref);   
        //     speed_ref_ref += 0.001;
        // }

        if (speed_mode == 1) 
        {
            if (speed_counter ==0)
            {
                speed_ref_ref = 0;
                speed_counter = 1;
            }

            if (speed_counter == 1)
            {
                speed_ref = 1.0;
                if (speed_ref_ref > 2.0) speed_counter = 2;
            }

            if (speed_counter == 2)
            {
                speed_ref = speed_ref_ref - 1.0;
                if (speed_ref_ref > 2.5) speed_counter = 3;
            }

            if (speed_counter == 3)
            {
                speed_ref = 1.5;
                if (speed_ref_ref > 2.8) speed_counter = 4;
            }

            if (speed_counter == 4)
            {
                speed_ref = 4.3 - speed_ref_ref;
                if (speed_ref_ref > 3.5) speed_counter = 5;
            }

            if (speed_counter == 5)
            {
                speed_ref = 0.8;
                if (speed_ref_ref > 4.0) speed_counter = 6;
            }

            if (speed_counter == 6)
            {
                speed_ref = 1.5 * speed_ref_ref - 5.2;
                if (speed_ref_ref > 4.4) speed_counter = 7;
            }

            if (speed_counter == 7)
            {
                speed_ref = 1.4;
            }

            speed_ref_ref += 0.0005;
        }

        if (speed_mode == 2)  //slow and fast,  range: 0.8-1.3
        {
            if (speed_counter == 0)
            {
                speed_ref = 1.3;
                speed_ref_ref += 0.001;
                if (speed_ref_ref >= 1.0)
                    speed_counter = 1;
            }
            else
            {
                speed_ref = 0.8;
                speed_ref_ref -= 0.001;
                if (speed_ref_ref <= 0.0)
                    speed_counter = 0;
            }
            
        }

        // Speed PID controller
        if (Flag_motor_start==0) {
            steer_pwm_cmd = 0.0;
            speed_pwm_cmd = 0.0;
        }
        else {
            steer_pwm_cmd = steer_pwm_cmd;
            //speed_pwm_cmd = speed_PIDcontrol.calculate_Kp_variant(current_speed, speed_ref, x_PID_speed, 80, 10, 0.1, 1.5, dt, Flag_motor_start);
            speed_pwm_cmd = speed_PIDcontrol.calculate(current_speed, speed_ref, x_PID_speed, dt, Flag_motor_start);
        }

        time_check_end = ros::WallTime::now();
        time_check_calc = (time_check_end-time_check_start).toNSec()*1e-6;
        //ROS_INFO_STREAM("Exectution time (ms): " << time_check_calc);

        //fprintf(stdout,"Pos. X = %.2f, Pos. Y = %.2f, Pos. Z = %.2f \n", pos_x, pos_y, pos_z);
        //fprintf(stdout,"Angle (Opti) X = %.2f, Angle (Opti) Y = %.2f, Angle (Opti) Z = %.2f \n", angle_Optitrack_x, angle_Optitrack_y, angle_Optitrack_z);

        
        //fprintf(stdout,"Gyroscope X = %.2f, Gyroscope Y = %.2f, Gyroscope Z = %.2f \n", gyro_x*RAD2DEG, gyro_y*RAD2DEG, gyro_z*RAD2DEG);
        //fprintf(stdout,"Acceleration X = %.2f, Acceleration Y = %.2f, Acceleration Z = %.2f \n", acc_x, acc_y, acc_z);
        //fprintf(stdout,"Angle X = %.2f, Angle Y = %.2f, Angle Z = %.2f \n", angle_x*RAD2DEG, angle_y*RAD2DEG, angle_z*RAD2DEG);
        //fprintf(stdout,"Pos. X = %.2f, Pos. Y = %.2f, Pos. Z = %.2f \n", pos_x, pos_y, pos_z);
        //fprintf(stdout,"Angle (Opti) X = %.2f, Angle (Opti) Y = %.2f, Angle (Opti) Z = %.2f \n", angle_Optitrack_x*RAD2DEG, angle_Optitrack_y*RAD2DEG, angle_Optitrack_z*RAD2DEG);

        fprintf(stdout,"===============================\n");
        //fprintf(stdout,"count = %d\n",count);
        

        //fprintf(stdout,"speed_current = %.2f, speed_cmd = %.2f, steer_cmd = %.2f\n", current_speed,speed_pwm_cmd, steer_pwm_cmd);
		//fprintf(stdout,"speed_current = %.2f, speed_cmd = %.2f, steer_cmd = %.2f, speed_error = %.2f, speed_error_integration = %.2f, speed_error_derivative = %.2f, kp = %.2f\n", current_speed,speed_pwm_cmd, steer_pwm_cmd,speed_PIDcontrol.get_error(),speed_PIDcontrol.get_error_integration(), speed_PIDcontrol.get_error_derivative(),speed_PIDcontrol.get_Kp());
		//fprintf(stdout,"y_err = %.2f, theta_err = %.2f\n", y_e,theta_e);
        
        // Publish the trajectory of the RC car
        pose_car.header.stamp = ros::Time::now();
        pose_car.pose.position.x = pos_x;
        pose_car.pose.position.y = pos_y;
        pose_car.pose.position.z = 0; 			// Set z = 0;
        pose_car.pose.orientation.x = 0.0;
        pose_car.pose.orientation.y = 0.0;
        pose_car.pose.orientation.z = 0.0;
        pose_car.pose.orientation.w = 1.0;
        path_car.poses.push_back(pose_car);

        path_car.header.stamp = ros::Time::now();
        path_car.header.frame_id = "world"; 	// Need to set the frame id
        //pub_path_car.publish(path_car);

        // Publish the speed_pwm_cmd and steer_pwm_cmd to "control_signal" topic
        if(Flag_control_start){
            dat.header.stamp = ros::Time::now();
            dat.accel=speed_pwm_cmd>SPEED_PWM_MAX?SPEED_PWM_MAX:speed_pwm_cmd<-SPEED_PWM_MAX?-SPEED_PWM_MAX:speed_pwm_cmd;
            dat.steer=steer_pwm_cmd;
            dat.status = 1;
            pub.publish(dat);
        }
        
        imu_filtered.angular_velocity.x = gyroX_filtered;
		imu_filtered.angular_velocity.y = gyroY_filtered;
		imu_filtered.angular_velocity.z = gyroZ_filtered;

		imu_filtered.linear_acceleration.x = accX_filtered;
		imu_filtered.linear_acceleration.y = accY_filtered;
		imu_filtered.linear_acceleration.z = accZ_filtered;

		imu_filtered.header.stamp = ros::Time::now();

		pub1.publish(imu_filtered);

        // Publish the trajectory data to "path_ref" topic
        pub_path.publish(path_ref);

        time_ros_last = time_ros_current;

        std::cout << cut_in << std::endl;
        
        if(ros::Time::now().toSec()-time_exp_start > 1.0)
        {
            if (pos_x_cutin > 2.9 || pos_x_cutin < 0.1) 
            {
                if (cut_in_mode == 0)
                {
                    t_cutin = ros::Time::now().toSec()-time_exp_start;
                    cut_in_mode = 1;
                }
                if (ros::Time::now().toSec()-time_exp_start - t_cutin > 5.0) //time until MPC change
                cut_in = 1;
            }
        }


        if(Flag_csv_output){
            //myfile <<ros::Time::now().toSec()-time_exp_start<<","<<px<<","<<py<<","<<pos_z<<","<<vx<<","<<
                //vy<<","<<u<<","<<y_e<<","<<theta_e<<","<<theta_d_lane<<","<<ahead_theta_d<<","<<y_e_dot<<","<<theta_e_dot<<","<<
                //delta_theta_d_lane<<","<<speed_pwm_cmd<<","<<steer_pwm_cmd<<gyro_x<<","<<gyro_y<<","<<gyro_z<<","<<
                //acc_x<<","<<acc_y<<","<<acc_z<<","<<angle_x<<","<<angle_y<<","<<angle_z<<
                //angle_Optitrack_x<<","<<angle_Optitrack_y<<","<<angle_Optitrack_z<<endl;
            //myfile <<ros::Time::now().toSec()-time_exp_start<<","<<px<<","<<py<<","<<pos_z<<","<<vx<<","<<
                //vy<<","<<u<<","<<y_e<<","<<theta_e<<","<<theta_d_lane<<","<<ahead_theta_d<<","<<y_e_dot<<","<<theta_e_dot<<","<<
                //delta_theta_d_lane<<","<<speed_pwm_cmd<<","<<steer_pwm_cmd<<current_speed<<endl;       
            //myfile <<ros::Time::now().toSec()-time_exp_start<<","<<vx<<","<<vy<<","<<gyro_x<<","<<gyroX_filtered<<","<<gyro_y<<","<<gyroY_filtered<<","<<gyro_z<<","<<gyroZ_filtered<<","<<acc_x<<","<<accX_filtered<<","<<acc_y<<","<<accY_filtered<<","<<acc_z<<","<<accZ_filtered<<endl;   
            //myfile <<ros::Time::now().toSec()-time_exp_start<<","<<px<<","<<py<<","<<pz<<","<<vx<<","<<vy<<","<<sqrt(vx*vx+vy*vy)<<","<<speed_ref<<","<<vz<<","<<gyroX_filtered<<","<<gyroY_filtered<<","<<gyroZ_filtered<<","<<accX_filtered<<","<<accY_filtered<<","<<accZ_filtered<<endl;
            myfile <<ros::Time::now().toSec()-time_exp_start<<","<<sqrt(vx*vx+vy*vy)<<","<<u<<endl;   
        }

        ros::spinOnce();
        loop_rate.sleep();
    }
    if(Flag_csv_output) myfile.close();
    return 0;
}
