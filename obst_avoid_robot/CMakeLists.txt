cmake_minimum_required(VERSION 2.8.3)
project(obst_avoid_robot)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  sensor_msgs
  tf
  visualization_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

catkin_package(
  INCLUDE_DIRS
    include
  CATKIN_DEPENDS
    roscpp
    geometry_msgs
    sensor_msgs
    visualization_msgs
    tf
)

######################### Executables #########################

add_executable(logo 
  src/nodes/logo.cpp
) 
target_link_libraries(logo 
  ${catkin_LIBRARIES}
)

add_executable(avoid_obstacles 
	src/nodes/avoid_obstacles_node.cpp
	src/avoid_obstacles.cpp
) 
target_link_libraries(avoid_obstacles 
  ${catkin_LIBRARIES}
)
add_dependencies(avoid_obstacles 
  ${catkin_EXPORTED_TARGETS}
)

add_executable(robot_tf_listener
  src/nodes/robot_tf_listener_node.cpp
  src/robot_tf_listener.cpp
)
target_link_libraries(robot_tf_listener
  ${catkin_LIBRARIES}
)

add_executable(bounding_box 
  src/nodes/bounding_box.cpp
)
target_link_libraries(bounding_box 
  ${catkin_LIBRARIES}
)
