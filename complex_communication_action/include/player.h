#ifndef PLAYER_H
#define PLAYER_H

#include "ros/ros.h"
#include <actionlib/server/simple_action_server.h>
#include <complex_communication_action/BoardAction.h>
#include <complex_communication_action/Terminate.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

class Player
{
	private:
		ros::NodeHandle n_; 

		actionlib::SimpleActionServer<complex_communication_action::BoardAction> as_;
		complex_communication_action::BoardResult result_;

		// Subscribers
		ros::Subscriber sub_;

	    // Random variables
	    std::string action_name_;
		int turn_;

		// Callbacks
		void executeCB		(const complex_communication_action::BoardGoalConstPtr &goal);
		void nodeShutdown	(complex_communication_action::Terminate msg);
			
	public:
		Player 				(string name, int turn);
		~Player 			(void);
};

#endif // PLAYER_H