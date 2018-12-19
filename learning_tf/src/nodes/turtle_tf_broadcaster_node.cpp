#include <learning_tf/turtle_tf_broadcaster.h>

int main(int argc, char** argv){
  
  ros::init(argc, argv, "turtle_tf_broadcaster");
  
  if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  string turtle_name = argv[1];

  ros::NodeHandle nh;
  learning_tf::TurtleTfBroadcaster obj(ros::NodeHandle nh, string turtle_name);

  ros::spin();
  return 0;
};