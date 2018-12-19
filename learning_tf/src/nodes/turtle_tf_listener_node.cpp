#include <learning_tf/turtle_tf_listener.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "turtle_tf_listener");

  ros::NodeHandle nh;
  learning_tf::TurtleTfListener listener(nh); 

  ros::spin();
  return 0;
}