#include <obst_avoid_robot/avoid_obstacles.h>

int main(int argc, char **argv)
{
	ros::init(argc, argv, "avoid_obstacles");
	ros::NodeHandle nh;
	
	obst_avoid_robot::AvoidObstacles obj(nh);
	
	ros::spin();
	return 0;
}