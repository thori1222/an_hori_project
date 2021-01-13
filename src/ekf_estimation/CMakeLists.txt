cmake_minimum_required(VERSION 2.8.3)
project(ekf_estimation)

#set(CMAKE_CXX_STANDARD, 11)
set(CMAKE_CXX_FLAGS "-O2 -std=c++11 -Wall ...")

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
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

add_executable(ekf_estimation src/state_estimation_EKF_6D.cpp)

target_link_libraries(ekf_estimation
 ${catkin_LIBRARIES}
 )
