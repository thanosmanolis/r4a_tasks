#include <param_communication/streamer.h>

int main(int argc, char **argv)
{
  // Set up ROS.
  ros::init(argc, argv, "streamer");
  ros::NodeHandle nh;

  // Create a new param_communication::Talker object.
  param_communication::Streamer node(nh);

  // Let ROS handle all callbacks.
  ros::spin();

  return 0;
}  // end main()
