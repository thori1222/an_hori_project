cmake_minimum_required(VERSION 2.8.11)
project(udp_connector_lib)
find_package(catkin REQUIRED COMPONENTS
        roscpp
        )

set(CMAKE_CXX_FLAGS "-O2 -Wall ${CMAKE_CXX_FLAGS}")

catkin_package(
        INCLUDE_DIRS include
        LIBRARIES udp_connector_lib
        CATKIN_DEPENDS roscpp
)

include_directories(udp_connector_lib
        include
        ${catkin_INCLUDE_DIRS}
        )

add_library(udp_connector_lib
        src/udp_connector.cpp
        )
target_link_libraries(udp_connector_lib
        ${catkin_LIBRARIES}
        )

add_dependencies(udp_connector_lib
        ${catkin_EXPORTED_TARGETS}
        )

install(DIRECTORY include/${PROJECT_NAME}/
        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
        FILES_MATCHING PATTERN "*.h"
        )


install(TARGETS udp_connector_lib
        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
        )      