cmake_minimum_required(VERSION 3.0.2)
project(manual_controller)

set (CMAKE_CXX_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  tf
  custom_pkg
)

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

catkin_package(
INCLUDE_DIRS include
)

include_directories(
include
${EIGEN3_INCLUDE_DIRS}
${catkin_INCLUDE_DIRS}
)


# add_executable(manual_publisher src/controller.cpp)
add_executable(manual_publisher src/Car.cpp src/Car_control.cpp src/controller_calc_manual.cpp)
# add_executable(manual_publisher src/Car.cpp src/Car_control.cpp src/controller_handle.cpp)

target_link_libraries(manual_publisher
  ${catkin_LIBRARIES}
)
