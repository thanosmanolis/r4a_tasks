#ifndef VICTIM_ANNOUNCE_H
#define VICTIM_ANNOUNCE_H

#include "ros/ros.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <simple_robot/GetRobotPoseAction.h>
#include <simple_robot/VictimFound.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

typedef actionlib::SimpleActionClient<simple_robot::GetRobotPoseAction> action_client;

class VictimAnnounce
{
	private:
		ros::NodeHandle n_;

		action_client *ac_;
		simple_robot::GetRobotPoseGoal goal;

		//Subscriber
		ros::Subscriber sub_;

		// Random functions & Callbacks
		void callRobotPose	(action_client *ac);
		void victimCallBack	(const simple_robot::VictimFound::ConstPtr& msg);

	public:
		VictimAnnounce 	(void);
		~VictimAnnounce (void);
};

#endif // VICTIM_ANNOUNCE_H