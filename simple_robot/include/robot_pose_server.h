#ifndef ROBOT_POSE_H
#define ROBOT_POSE_H

#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <simple_robot/GetRobotPoseAction.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

class RobotPose
{
	private:
		ros::NodeHandle n_; 

		actionlib::SimpleActionServer<simple_robot::GetRobotPoseAction> as_;
		simple_robot::GetRobotPoseResult result_;

		// Subscribers
		ros::Subscriber sub_;

	    // Random variables
	    std::string action_name_;

		// Callbacks
		void executeCB	(const simple_robot::GetRobotPoseGoalConstPtr &goal);
			
	public:
		RobotPose 	(string name);
		~RobotPose 	(void);
};

#endif // ROBOT_POSE_H