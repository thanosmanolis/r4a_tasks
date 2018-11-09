cmake_minimum_required(VERSION 2.8.3)
project(simple_robot)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  actionlib
  message_generation
  simple_robot_msgs
)

find_package(Boost REQUIRED COMPONENTS 
  system
  thread
)

add_message_files(
  DIRECTORY ../simple_robot_msgs/msg
  FILES TemperatureReading.msg VictimFound.msg
)

add_action_files(
  DIRECTORY ../simple_robot_msgs/action
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

add_executable(logo 
  src/logo.cpp)
target_link_libraries(logo 
  ${catkin_LIBRARIES})

add_executable(thermal_sensor 
  src/thermal_sensor.cpp)
target_link_libraries(thermal_sensor 
  ${catkin_LIBRARIES})
add_dependencies(thermal_sensor 
  ${PROJECT_NAME}_generate_messages_cpp 
  ${catkin_EXPORTED_TARGETS})

add_executable(data_fusion 
  src/data_fusion.cpp)
target_link_libraries(data_fusion 
  ${catkin_LIBRARIES})
add_dependencies(data_fusion 
  ${PROJECT_NAME}_generate_messages_cpp 
  ${catkin_EXPORTED_TARGETS})

add_executable(robot_pose_server 
  src/robot_pose_server.cpp)
target_link_libraries(robot_pose_server 
  ${catkin_LIBRARIES})
add_dependencies(robot_pose_server 
  ${PROJECT_NAME}_generate_messages_cpp 
  ${catkin_EXPORTED_TARGETS})

add_executable(victim_announce 
  src/victim_announce.cpp)
target_link_libraries(victim_announce 
  ${catkin_LIBRARIES})
add_dependencies(victim_announce 
  ${PROJECT_NAME}_generate_messages_cpp 
  ${catkin_EXPORTED_TARGETS})