cmake_minimum_required(VERSION 2.8.3)
project(cacc_communicator)

add_compile_options(-std=c++11)

find_package(Eigen3 QUIET)

if (NOT EIGEN3_FOUND)
    # Fallback to cmake_modules
    find_package(cmake_modules REQUIRED)
    find_package(Eigen REQUIRED)
    set(EIGEN3_INCLUDE_DIRS ${EIGEN_INCLUDE_DIRS})
    set(EIGEN3_LIBRARIES ${EIGEN_LIBRARIES})  # Not strictly necessary as Eigen is head only
    # Possibly map additional variables to the EIGEN3_ prefix.
else ()
    set(EIGEN3_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})
endif ()


## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS roscpp rospy std_msgs tf geometry_msgs cacc_msgs udp_connector_lib dynamic_reconfigure)
 
generate_dynamic_reconfigure_options(
  cfg/carParam.cfg
)

## Declare a catkin package 
catkin_package(
    INCLUDE_DIRS include
    CATKIN_DEPENDS message_runtime roscpp std_msgs nav_msgs geometry_msgs cacc_msgs tf message_filters udp_connector_lib
)


## Build 
include_directories(
    include 
    ${catkin_INCLUDE_DIRS}
    ${EIGEN3_INCLUDE_DIRS}
)

add_executable(car_sender nodes/car/car_sender.cpp)
target_link_libraries(car_sender ${catkin_LIBRARIES})
add_dependencies(car_sender cacc_communicator_gencfg ${catkin_EXPORTED_TARGETS})

add_executable(car_receiver nodes/car/car_receiver.cpp)
target_link_libraries(car_receiver ${catkin_LIBRARIES})
add_dependencies(car_receiver ${catkin_EXPORTED_TARGETS})

add_executable(controller_sender nodes/controller/controller_sender.cpp)
target_link_libraries(controller_sender ${catkin_LIBRARIES})
add_dependencies(controller_sender ${catkin_EXPORTED_TARGETS})

add_executable(controller_receiver nodes/controller/controller_receiver.cpp nodes/controller/Course.cpp)
target_link_libraries(controller_receiver ${catkin_LIBRARIES})
add_dependencies(controller_receiver ${catkin_EXPORTED_TARGETS})
