#ifndef	TURTLE_TF_BROADCASTER_H
#define TURTLE_TF_BROADCASTER_H

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

using namespace std;

namespace learning_tf
{
class TurtleTfBroadcaster
{
	private:
		string turtle_name_;
		ros::NodeHandle nh_;

		//! ROS Subscriber
		ros::Subscriber sub_;
 
		//! Create object to copy the info from the 2D pose into the 3D transform.
		tf::Transform transform_;

		//! Create object to set the rotation.
		tf::Quaternion rot_;

		//! Random Function
		void poseCallback(const turtlesim::PoseConstPtr& msg);

	public:
		TurtleTfBroadcaster 	(ros::NodeHandle nh, string turtle_name);
		~TurtleTfBroadcaster 	(void); 
};
}

#endif