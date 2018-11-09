cmake_minimum_required(VERSION 2.8.3)
project(param_communication)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS 
  roscpp
  rospy
  std_msgs
  message_generation
  dynamic_reconfigure
)

add_message_files(
  FILES 
  Num.msg
)

generate_messages(
  DEPENDENCIES 
  std_msgs
)

generate_dynamic_reconfigure_options(
  cfg/params.cfg
)

catkin_package(
  CATKIN_DEPENDS 
	dynamic_reconfigure
  message_runtime
  roscpp 
  rospy
  std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(logo 
  src/nodes/logo.cpp)
target_link_libraries(logo 
  ${catkin_LIBRARIES})

add_executable(streamer src/nodes/streamer_node.cpp src/streamer.cpp)
target_link_libraries(streamer ${catkin_LIBRARIES})
add_dependencies(streamer param_communication_generate_messages_cpp)

add_executable(manipulator src/nodes/manipulator_node.cpp src/manipulator.cpp)
target_link_libraries(manipulator ${catkin_LIBRARIES})
add_dependencies(manipulator param_communication_gencfg param_communication_generate_messages_cpp)