cmake_minimum_required(VERSION 2.8.3)
project(learning_tf)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  turtlesim
)

catkin_package(
#  INCLUDE_DIRS include
#  CATKIN_DEPENDS roscpp rospy tf turtlesim
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

#######################
##    Executables    ##
#######################

add_executable(logo
  src/nodes/logo.cpp
)
target_link_libraries(logo
  ${catkin_LIBRARIES}
)

add_executable(turtle_tf_broadcaster
 	src/nodes/turtle_tf_broadcaster_node.cpp
	src/turtle_tf_broadcaster.cpp
)
target_link_libraries(turtle_tf_broadcaster
	${catkin_LIBRARIES}
)

add_executable(turtle_tf_listener
  src/nodes/turtle_tf_listener_node.cpp
  src/turtle_tf_listener.cpp
)
target_link_libraries(turtle_tf_listener
  ${catkin_LIBRARIES}
)

add_executable(frame_tf_broadcaster 
  src/nodes/frame_tf_broadcaster_node.cpp
)
target_link_libraries(frame_tf_broadcaster
  ${catkin_LIBRARIES})