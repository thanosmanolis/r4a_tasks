#include <learning_tf/turtle_tf_broadcaster.h>

namespace learning_tf
{

/*
*********************
*    Constructor    * 
*********************
*/

TurtleTfBroadcaster::TurtleTfBroadcaster(ros::NodeHandle nh, string turtle_name): 
	nh_(nh),
	turtle_name_(turtle_name)
{
	sub_ = nh_.subscribe(turtle_name_+"/pose", 10, &TurtleTfBroadcaster::poseCallback, this);
}

/*
********************
*    Destructor    *  
********************
*/

TurtleTfBroadcaster::~TurtleTfBroadcaster(void)
{
    ROS_INFO("[TurtleTfBroadcaster] Node destroyed.");
}

/*
************************
*    Pose Callback.    *  
************************
*/

void TurtleTfBroadcaster::poseCallback(const turtlesim::PoseConstPtr& msg)
{
	transform_.setOrigin( tf::Vector3(msg->x, msg->y, 0.0) );
	rot_.setRPY(0, 0, msg->theta);
	transform_.setRotation(rot_);

	//! Create object to send info over the wire.
  	static tf::TransformBroadcaster br;
	br.sendTransform(tf::StampedTransform(transform_, ros::Time::now(), "world", turtle_name_));
}

}