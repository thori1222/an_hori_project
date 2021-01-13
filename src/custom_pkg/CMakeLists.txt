cmake_minimum_required(VERSION 2.8.3)
project(custom_pkg)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  message_generation
)

## Generate messages in the 'msg' folder
 add_message_files(
   DIRECTORY msg
   FILES
   control_signal.msg
   six_states.msg
)

## Generate added messages and services with any dependencies listed here
 generate_messages(
   DEPENDENCIES
   std_msgs  # Or other packages containing msgs
)
catkin_package(
  CATKIN_DEPENDS roscpp std_msgs sensor_msgs tf
)

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)



