#include <obst_avoid_robot/robot_tf_listener.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_listener");

  ros::NodeHandle nh;
  obst_avoid_robot::RobotTfListener listener(nh); 

  ros::spin();
  return 0;
}