#include <usb_cam_input/get_input.h>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "get_input");

	usb_cam_input::GetInput obj();

	ros::spin();
	return 0;
}