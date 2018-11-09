#include "victim_announce.h"

/*
*********************
*	 Constructor    *	
*********************
*/

VictimAnnounce::VictimAnnounce(void)
{
	sub_ = n_.subscribe("/data_fusion/victim_found", 1000, &VictimAnnounce::victimCallBack, this);

	ac_ = new action_client("/slam/get_robot_pose", true);

	ROS_INFO("***************************************");
	ROS_INFO("Waiting for server to start.          *");
	ROS_INFO("***************************************");
	
	// wait for the action server to start
	ac_->waitForServer();

	ROS_INFO("***************************************");
	ROS_INFO("Server started.                       *");
	ROS_INFO("[victim_announce] Node initialised.   *");
	ROS_INFO("***************************************");
}

/*
********************
*	 Destructor    *	
********************
*/

VictimAnnounce::~VictimAnnounce(void)
{
	ROS_INFO("[Server] Node destroyed");
}

/*
***********************************************
*	 Announces the victim's pose if found.    *	
***********************************************
*/	

void VictimAnnounce::victimCallBack(const simple_robot::VictimFound::ConstPtr& msg)
{
	callRobotPose(ac_);
}

/*
**************************
*	 Prints the pose.    *	
**************************
*/	

void VictimAnnounce::callRobotPose(action_client *ac)
{
	ac->sendGoal(goal);
	bool finished_before_timeout = ac->waitForResult(ros::Duration(30.0));

	if (finished_before_timeout)
	{
		actionlib::SimpleClientGoalState state = ac->getState();
		ROS_INFO("*******************************************************************************");
		ROS_INFO("Action of server finished: %s                                          *", state.toString().c_str());

		const simple_robot::GetRobotPoseResult::ConstPtr& result = ac->getResult();
		ROS_INFO("Victim found! Robot Pose = (%d,%d). Sensor used for identification: thermal     *", result->x, result->y);
		ROS_INFO("*******************************************************************************");
    }
}

/*
***********************
*	 Main Function    *	
***********************
*/

int main(int argc, char **argv)		
{
	ros::init(argc, argv, "victim_announce");
	VictimAnnounce announce;
	ros::spin();

	return 0;
}