cmake_minimum_required(VERSION 2.8.3)
project(complex_communication_msg)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_message_files(
  FILES
  Board.msg
)

generate_messages(
  DEPENDENCIES 
  std_msgs  # Or other packages containing msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES complex_communication_msg
   CATKIN_DEPENDS message_runtime roscpp std_msgs
#  DEPENDS system_lib
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(logo 
  src/logo.cpp)
target_link_libraries(logo 
  ${catkin_LIBRARIES})

add_executable(server_node 
  src/server.cpp
  src/server_node.cpp)
target_link_libraries(server_node 
  ${catkin_LIBRARIES})
add_dependencies(server_node
  complex_communication_msg_gencpp)

add_executable(player_1 
  src/player.cpp
  src/player_1.cpp)
target_link_libraries(player_1 
  ${catkin_LIBRARIES})
add_dependencies(player_1 
  complex_communication_msg_gencpp)

add_executable(player_2
  src/player.cpp
  src/player_2.cpp)
target_link_libraries(player_2 
  ${catkin_LIBRARIES})
add_dependencies(player_2
  complex_communication_msg_gencpp)