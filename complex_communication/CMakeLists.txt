cmake_minimum_required(VERSION 2.8.3)
project(complex_communication)

# add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
)

add_service_files(
  FILES
  Move.srv
)

generate_messages(
  DEPENDENCIES 
  std_msgs  # Or other packages containing msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES complex_communication
   CATKIN_DEPENDS roscpp std_msgs message_runtime
#  DEPENDS system_lib 
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)

add_executable(logo src/logo.cpp)
target_link_libraries(logo ${catkin_LIBRARIES})

add_executable(server src/server.cpp)
target_link_libraries(server ${catkin_LIBRARIES})
add_dependencies(server complex_communication_gencpp)

add_executable(player_1 src/player_1.cpp)
target_link_libraries(player_1 ${catkin_LIBRARIES})
add_dependencies(player_1 complex_communication_gencpp)

add_executable(player_2 src/player_2.cpp)
target_link_libraries(player_2 ${catkin_LIBRARIES})
add_dependencies(player_2 complex_communication_gencpp)