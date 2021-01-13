cmake_minimum_required(VERSION 2.8.11)
project(cgmres_lib)
find_package(catkin REQUIRED COMPONENTS
        roscpp
)

set(CMAKE_CXX_FLAGS "-O2 -Wall ${CMAKE_CXX_FLAGS}")

catkin_package(
        INCLUDE_DIRS include
        #LIBRARIES cgmres_lib
        CATKIN_DEPENDS roscpp
)

include_directories(cgmres_lib
        include
        ${catkin_INCLUDE_DIRS}
        )

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.hpp"
        )

install(DIRECTORY include/${PROJECT_NAME}/Base
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h"
        )


# install(TARGETS cgmres_lib
#         ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#         LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#         RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#         )      