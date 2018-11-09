#include "robot_pose_server.h"

/*
*********************
*	 Constructor    *	
*********************
*/
		
RobotPose::RobotPose(string name):
	as_(n_, name, boost::bind(&RobotPose::executeCB, this, _1), false),
	action_name_(name)
{
	as_.start();

	ROS_INFO("****************************************");
	ROS_INFO("[robot_pose_server] Node initialized.  *");
	ROS_INFO("****************************************");
}

/*
********************
*	 Destructor    *	
********************
*/

RobotPose::~RobotPose(void)
{
	ROS_INFO("[robot_pose_server] Node destroyed.");
}

/*
*****************************************************************
*	 Fill the action’s result with two random integer values    *	
*****************************************************************
*/

void RobotPose::executeCB(const simple_robot::GetRobotPoseGoalConstPtr &goal) 
{ 
	bool success = true;
    ROS_INFO("************************************");
	ROS_INFO("Action server called               *");

	if (as_.isPreemptRequested() || !ros::ok())
	{
		ROS_INFO("%s: Preempted.        *", action_name_.c_str());
		as_.setPreempted();
		success = false;
	}

	srand(time(NULL));
	
	int x = rand()%10;
	int y = rand()%10;

	if(success)
	{
		result_.x = x;
		result_.y = y;

		ROS_INFO("%s: Succeeded    *", action_name_.c_str());
		ROS_INFO("************************************");
		// set the action state to succeeded
		as_.setSucceeded(result_);
	}
}

/*
***********************
*	 Main Function    *	
***********************
*/

int main(int argc, char **argv)		
{
	ros::init(argc, argv, "robot_pose_server");
	RobotPose pose("/slam/get_robot_pose");
	ros::spin();

	return 0;
}