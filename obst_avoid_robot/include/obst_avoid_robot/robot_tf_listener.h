#ifndef ROBOT_TF_LISTENER_H
#define ROBOT_TF_LISTENER_H

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

using namespace std;

namespace obst_avoid_robot
{
class RobotTfListener
{
	private:
		ros::NodeHandle nh_;

		//! ROS Publisher
		ros::Publisher pub_marker_vel_;

		//! Create object to receive tf transformations and buffer them for 10 secs.
		tf::TransformListener listener_;

		//! Create object to publish Twist type messages.
		geometry_msgs::Twist vel_msg_;

		//! Create object to get the robot pose (and use it to calculate
		//! the new linear and angular velocites for marker).
		tf::StampedTransform transform_;

		//! Random Functions
		void spawnMarker	(void);
		void followRobot 	(void);

	public:
		RobotTfListener 	(ros::NodeHandle nh);
		~RobotTfListener 	(void);

};
}

#endif