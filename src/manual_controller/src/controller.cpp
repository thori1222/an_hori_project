#include <ros/ros.h>
#include <custom_pkg/control_signal.h>
#include <sensor_msgs/Joy.h>

custom_pkg::control_signal dat;

void joy_callback(const sensor_msgs::Joy& joy_msg)
{
  if (joy_msg.axes[1] >= 0)
  dat.accel = 20 * joy_msg.axes[1];
  else 
  dat.accel = -60 + 20 * joy_msg.axes[1];
  dat.steer = 500 * joy_msg.axes[2];
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "manual_publisher");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<custom_pkg::control_signal>("control_signal", 50);
  ros::Subscriber joy_sub = nh.subscribe("joy", 50, joy_callback);

  ros::Rate loop_rate(10);
  while (ros::ok())
  {
    pub.publish(dat);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

