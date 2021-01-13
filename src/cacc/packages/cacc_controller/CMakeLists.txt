cmake_minimum_required(VERSION 2.8.3)
project(cacc_controller)

## Compile as C++11, supported in ROS Kinetic and newer
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

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  cgmres_lib
  cacc_msgs
  dynamic_reconfigure
)
find_package(Boost REQUIRED)

generate_dynamic_reconfigure_options(
  cfg/MpcParam.cfg
)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp cgmres_lib cacc_msgs
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
 include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${EIGEN3_INCLUDE_DIRS}
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(state_estimator nodes/state_estimator/state_estimator.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(state_estimator ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(state_estimator
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(platooning_cgmres nodes/platooning_control/solver_cgmres.cpp)
add_dependencies(platooning_cgmres cacc_controller_gencfg ${catkin_EXPORTED_TARGETS})
target_link_libraries(platooning_cgmres
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(following_controller nodes/following_control/following_controller.cpp)
add_dependencies(following_controller  ${catkin_EXPORTED_TARGETS})
target_link_libraries(following_controller
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)

add_executable(model_estimator nodes/model_estimator/model_estimator.cpp)
add_dependencies(model_estimator  ${catkin_EXPORTED_TARGETS})
target_link_libraries(model_estimator
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
)
