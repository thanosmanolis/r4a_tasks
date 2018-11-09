#include <ros/ros.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <simple_communication/Num.h>

using namespace std;

void randomNumberCallBack(const simple_communication::Num::ConstPtr& msg)
{
	int square = msg->num * msg->num;
	ROS_INFO("[Manipulator] %d", square);
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "manipulator");
	ros::NodeHandle n;

	ros::Subscriber sub = n.subscribe("/task1/numbers", 1000, randomNumberCallBack);

	ros::spin();
	return 0;
}