#ifndef TURTLE_TF_LISTENER_H
#define TURTLE_TF_LISTENER_H

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

using namespace std;

namespace learning_tf
{
class TurtleTfListener
{
	private:
		ros::NodeHandle nh_;

		//! ROS Publisher
		ros::Publisher pub_turtle_vel_;

		//! Create object to receive tf transformations and buffer them for 10 secs.
		tf::TransformListener listener_;

		//! Create object publish Twist type messages.
		geometry_msgs::Twist vel_msg_;

		//! Create object get the turtle1 pose (and use it to calculate
		//! the new linear and angular velocites for turtle2).
		tf::StampedTransform transform_;

		//! Random Functions
		void spawnTurtle	(void);
		void followTurtle	(void);

	public:
		TurtleTfListener 	(ros::NodeHandle nh);
		~TurtleTfListener 	(void);

};
}

#endif