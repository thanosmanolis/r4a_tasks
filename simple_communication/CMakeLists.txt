cmake_minimum_required(VERSION 2.8.3)
project(simple_communication)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS 
  roscpp
  std_msgs
  genmsg
)

add_message_files(
  FILES 
  Num.msg
)

generate_messages(
  DEPENDENCIES std_msgs)

catkin_package(
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(logo src/logo.cpp)
target_link_libraries(logo ${catkin_LIBRARIES})

add_executable(streamer src/streamer.cpp)
target_link_libraries(streamer ${catkin_LIBRARIES})
add_dependencies(streamer simple_communication_generate_messages_cpp)

add_executable(manipulator src/manipulator.cpp)
target_link_libraries(manipulator ${catkin_LIBRARIES})
add_dependencies(manipulator simple_communication_generate_messages_cpp)