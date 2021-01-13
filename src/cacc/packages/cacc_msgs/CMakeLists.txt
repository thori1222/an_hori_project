cmake_minimum_required(VERSION 2.8.3)
project(cacc_msgs)

find_package(catkin REQUIRED COMPONENTS 
    message_generation 
    std_msgs
)

add_message_files(
    FILES 
    CaccControlPacket.msg 
    CaccSensorPacket.msg
    CaccStatePacket.msg
    CaccMpcParam.msg
    CaccMpcState.msg
    PrarxParam.msg
)

generate_messages(
  DEPENDENCIES 
  std_msgs
)

## Declare a catkin package 
catkin_package(
    CATKIN_DEPENDS 
    message_runtime 
    std_msgs
)

