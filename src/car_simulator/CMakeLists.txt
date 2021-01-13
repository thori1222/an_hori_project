cmake_minimum_required(VERSION 2.8.3)
project(car_simulator)

set (CMAKE_CXX_STANDARD 11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
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

add_executable(car_simulator src/car_simulator.cpp )
add_dependencies(car_simulator  ${catkin_EXPORTED_TARGETS})
target_link_libraries(car_simulator
 ${catkin_LIBRARIES}
 )
