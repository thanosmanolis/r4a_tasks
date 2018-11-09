cmake_minimum_required(VERSION 2.8.3)
project(simple_robot_msgs)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  message_generation
)

find_package(Boost REQUIRED COMPONENTS 
  system
  thread
)

add_message_files(
  FILES TemperatureReading.msg VictimFound.msg
)

add_action_files(
  DIRECTORY action 
  FILES GetRobotPose.action
)

generate_messages(
  DEPENDENCIES
  actionlib_msgs 
  std_msgs 
)

catkin_package(
  CATKIN_DEPENDS roscpp actionlib message_runtime
  DEPENDS Boost
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)