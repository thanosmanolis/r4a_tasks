#ifndef	AVOID_OBSTACLES_H
#define AVOID_OBSTACLES_H

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

namespace obst_avoid_robot
{
class AvoidObstacles
{
	private:
		ros::NodeHandle nh_;
		geometry_msgs::Twist msg_speeds_;

		//! ROS Publisher
		ros::Publisher pub_;

		//! ROS Subscriber
		ros::Subscriber sub_;

		//! Random Functions
		void laserCallback	(const sensor_msgs::LaserScan::ConstPtr &msg);

	public:
		AvoidObstacles 	(ros::NodeHandle nh);
		~AvoidObstacles (void);
};
}

#endif