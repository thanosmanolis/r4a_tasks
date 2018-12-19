cmake_minimum_required(VERSION 2.8.3)
project(usb_cam_input)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES usb_cam_input
#  CATKIN_DEPENDS roscpp sensor_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(get_input 
	src/nodes/get_input_node.cpp
	src/get_input.cpp
) 
target_link_libraries(get_input 
  ${catkin_LIBRARIES}
)
add_dependencies(get_input 
  ${catkin_EXPORTED_TARGETS}
)