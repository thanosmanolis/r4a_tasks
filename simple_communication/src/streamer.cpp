#include <ros/ros.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <simple_communication/Num.h>

using namespace std;

int main(int argc, char **argv)
{
	ros::init(argc, argv, "streamer");
	ros::NodeHandle n;

	ros::Publisher pub = n.advertise<simple_communication::Num>("/task1/numbers", 1000);
	ros::Duration(0.5).sleep();
	ros::Rate loop_rate(1);

	int count = 0;
	while(ros::ok())
	{
		simple_communication::Num msg;

		srand(time(NULL));
		msg.num = rand()%20;

		ROS_INFO("[Streamer] %d", msg.num);
		pub.publish(msg);
		
		ros::spinOnce();
		loop_rate.sleep();
		count++;
	}
	
	return 0;
}