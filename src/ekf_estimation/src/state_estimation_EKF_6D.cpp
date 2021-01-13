#include "math.h"
#include "ros/ros.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "sensor_msgs/Imu.h"
#include "iostream"

#include <string>
#include <std_msgs/Float32MultiArray.h>

#include <ekf.h>
#include <car_model_6D.h>
#include <custom_pkg/six_states.h>

#define RAD2DEG 180.0/M_PI

using namespace std;
using namespace Eigen;


float gyro_x, gyro_y, gyro_z;
float acc_x, acc_y, acc_z;
float angle_x, angle_y, angle_z;

float angle_Optitrack_x, angle_Optitrack_y, angle_Optitrack_z;
float pos_x, pos_y, pos_z;

double time_OptiTrack_current, time_OptiTrack_last;

int Flag_control_start = 1;
float Flag_motor_start = 0.0;
/* =====================================================================
 * Receive data from IMU topic
 * =====================================================================
 */
void chatterCallback_IMU(const sensor_msgs::Imu::ConstPtr& msg)
{
    gyro_x = msg->angular_velocity.x*RAD2DEG;
    gyro_y = msg->angular_velocity.y*RAD2DEG;	// Convert ROS frame to IMU frame
    gyro_z = msg->angular_velocity.z*RAD2DEG;	// Convert ROS frame to IMU frame

    acc_x = msg->linear_acceleration.x;
    acc_y = msg->linear_acceleration.y;	// Convert ROS frame to IMU frame
    acc_z = msg->linear_acceleration.z;	// Convert ROS frame to IMU frame

    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg->orientation, quat);

    double roll, pitch, yaw;

    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    angle_y = roll * RAD2DEG;
    angle_x = -pitch * RAD2DEG;		// Convert ROS-frame to IMU-frame
    angle_z = yaw * RAD2DEG;  		// Convert ROS-frame to IMU-frame

    fprintf(stdout, "Gyroscope X = %.2f, Gyroscope Y = %.2f, Gyroscope Z = %.2f \n", gyro_x, gyro_y, gyro_z);
    fprintf(stdout, "Acceleration X = %.2f, Acceleration Y = %.2f, Acceleration Z = %.2f \n", acc_x, acc_y, acc_z);
    fprintf(stdout, "Angle X = %.2f, Angle Y = %.2f, Angle Z = %.2f \n", angle_x, angle_y, angle_z);

}


/* =====================================================================
 * Receive data from Motion Capture topic
 * =====================================================================
 */
void chatterCallback_Optitrack(const geometry_msgs::PoseStamped::ConstPtr& msg)
{

    time_OptiTrack_current = msg->header.stamp.sec + msg->header.stamp.nsec*1e-9;
    //fprintf(stdout,"time = %f\n",time_OptiTrack_current);

    pos_x = msg->pose.position.x;
    pos_y = msg->pose.position.y;	// Convert ROS frame to IMU frame
    pos_z = msg->pose.position.z;	// Convert ROS frame to IMU frame

    tf::Quaternion quat;
    tf::quaternionMsgToTF(msg->pose.orientation, quat);

    double roll_opti, pitch_opti, yaw_opti;

    tf::Matrix3x3(quat).getRPY(roll_opti, pitch_opti, yaw_opti);

    angle_Optitrack_x = roll_opti;		// In Ground Coordinate system
    angle_Optitrack_y = pitch_opti;		// In Ground Coordinate system
    angle_Optitrack_z = yaw_opti;  		// In Ground Coordinate system

    /*
    fprintf(stdout,"Pos. X = %.2f, Pos. Y = %.2f, Pos. Z = %.2f \n", pos_x, pos_y, pos_z);
    fprintf(stdout,"Angle (Opti) X = %.2f, Angle (Opti) Y = %.2f, Angle (Opti) Z = %.2f \n", angle_Optitrack_x, angle_Optitrack_y, angle_Optitrack_z);
    */
}

void chatterCallback_MotorSignal(const std_msgs::Float32MultiArray::ConstPtr& msg)
{
    Flag_motor_start = msg->data[2];

}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "state_estimation_EKF_3D_node");

    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("/imu/data", 100, chatterCallback_IMU);
    ros::Subscriber sub1 = n.subscribe("/vrpn_client_node/RigidBody/pose", 100, chatterCallback_Optitrack);
    ros::Subscriber sub2 = n.subscribe("/motor_signal", 100, chatterCallback_MotorSignal);

    ros::Publisher pub = n.advertise<std_msgs::Float32MultiArray>("/control_signal", 100);
	ros::Publisher state_pub = n.advertise<ekf_estimation::six_states>("/state_estimate",100);

    double lf, lr, m, Iz;
    double Kf, Kr, mu;
    double c_air, F_fric, q_std, r_std, vx_min;

    n.getParam("lf", lf);
    n.getParam("lr", lr);
    n.getParam("m", m);
    n.getParam("Iz", Iz);
    n.getParam("tire_model/Kf", Kf);
    n.getParam("tire_model/Kr", Kr);
    n.getParam("tire_model/mu", mu);
    n.getParam("air_drag_coeff", c_air);
    n.getParam("friction", F_fric);
    n.getParam("state_estimation/q_std", q_std);
    n.getParam("state_estimation/r_std", r_std);
    n.getParam("state_estimation/vx_min", vx_min);

    Eigen::MatrixXf vehicle_param(1, 4);
    Eigen::MatrixXf tire_param(1, 3);

    vehicle_param << lf, lr, m, Iz;
    tire_param << Kf, Kr, mu;

    double freq = 100;
    double dt = 1 / freq;
    ros::Rate loop_rate(freq);	// 100 Hz

    double t0;
    t0 = ros::Time::now().toSec();

    Eigen::MatrixXf state_ekf(1, 6);
    state_ekf << 1.0, 0.0, 0.0, 0.0, 0.0, 0.0;

    // diagonal matrices P, Q, R
    Eigen::MatrixXf P(6, 6);
    Eigen::MatrixXf Q(6, 6);
    Eigen::MatrixXf R(6, 6);
    P << 1, 0, 0, 0, 0, 0,
      0, 1, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0,
      0, 0, 0, 1, 0, 0,
      0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 1;
    Q << 0.01, 0, 0, 0, 0, 0,
      0, 0.01, 0, 0, 0, 0,
      0, 0, 0.01, 0, 0, 0,
      0, 0, 0, 100000.0, 0, 0,
      0, 0, 0, 0, 100000.0, 0,
      0, 0, 0, 0, 0, 1.0;
    R << 0.01, 0, 0, 0, 0, 0,
      0, 0.01, 0, 0, 0, 0,
      0, 0, 0.01, 0, 0, 0,
      0, 0, 0, 10.0, 0, 0,
      0, 0, 0, 0, 10.0, 0,
      0, 0, 0, 0, 0, 10.0;

    double vx, vy;
    double px, py, pz, car_yaw;
    double angle_Opt_x, angle_Opt_y, angle_Opt_z;

    double x_ekf, y_ekf, theta_ekf;
    double vx_ekf, vy_ekf, r_ekf;
    
    double steer, accel;

    ros::WallTime time_check_start, time_check_end;
	double time_ros_current, time_ros_last, time_check_calc;
    // START LOOOOOOOOOOOOP! ahihi
    while (ros::ok()) {
		angle_Opt_x = angle_Optitrack_x;
		angle_Opt_y = angle_Optitrack_y;
		angle_Opt_z = angle_Optitrack_z;
		
		time_ros_current = time_OptiTrack_current;
		dt = time_ros_current - time_ros_last;	// Calculate the sampling time

		x_ekf		= state_ekf(0, 0);
        y_ekf		= state_ekf(0, 1);
        theta_ekf	= state_ekf(0, 2);
        vx_ekf		= state_ekf(0, 3);
        vy_ekf		= state_ekf(0, 4);
        r_ekf		= state_ekf(0, 5);
        
        //save data to the message
        ekf_estimation::six_states six_states;
		six_states.X =   x_ekf;
		six_states.Y =   y_ekf;
		six_states.yaw = theta_ekf;
		six_states.vx =  vx_ekf;
		six_states.vy =  vy_ekf;
		six_states.yr =  r_ekf;

		// publish to /state_estimate
		state_pub.publish(six_states);

        Eigen::MatrixXf y(1, 2);
        Eigen::MatrixXf u(1, 2);
        Eigen::MatrixXf F_ext(1, 2);

        y << pos_x, pos_y, angle_Optitrack_z, gyro_z;
        u << steer, accel;
        F_ext << c_air, F_fric;

        std::vector<Eigen::MatrixXf> args;
        args.push_back(u);
        args.push_back(vehicle_param);
        args.push_back(tire_param);
        args.push_back(F_ext);

        // EKF update and calculation time check
        time_check_start = ros::WallTime::now();
        std::tie(state_ekf, P) = ekf(f_6D, state_ekf, P, h_6D, y, Q, R, args, dt);
        time_check_end = ros::WallTime::now();
        time_check_calc = (time_check_end - time_check_start).toNSec()*1e-6;
        fprintf(stdout,"Time EKF = %.2f [ms] \n",time_check_calc);

        time_ros_last = time_ros_current;
        //myfile << ros::Time::now().toSec() - time_exp_start << "," << px << "," << py << "," << pos_z << "," << vx << "," <<
               //vy << "," << u << "," << y_e << "," << theta_e << "," << theta_d_lane << "," << ahead_theta_d << "," << y_e_dot << "," << theta_e_dot << "," <<
               //delta_theta_d_lane << "," << speed_pwm_cmd << "," << steer_pwm_cmd << current_speed << endl;

        ros::spinOnce();
        loop_rate.sleep();
    }
    //myfile.close();
    return 0;
}
