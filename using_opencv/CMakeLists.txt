cmake_minimum_required(VERSION 2.8.3)
project(using_opencv)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  std_msgs
)

find_package(OpenCV REQUIRED)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES using_opencv
#  CATKIN_DEPENDS cv_bridge image_transport roscpp sensor_msgs std_msgs
#  CATKIN_DEPENDS opencv
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)

add_executable(image_converter 
  src/image_converter.cpp)
target_link_libraries(image_converter 
  ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(image_converter 
  ${catkin_EXPORTED_TARGETS})
