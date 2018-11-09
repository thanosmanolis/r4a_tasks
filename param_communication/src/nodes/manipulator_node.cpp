#include <param_communication/manipulator.h>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "manipulator");
  ros::NodeHandle nh;

  param_communication::Manipulator node(nh);

  ros::spin();

  return 0;
}
