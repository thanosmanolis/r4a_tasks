#ifndef SERVER_H
#define SERVER_H

#include "ros/ros.h"
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <complex_communication_action/BoardAction.h>
#include <complex_communication_action/Terminate.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

typedef actionlib::SimpleActionClient<complex_communication_action::BoardAction> action_client;

class Server
{
	private:
		ros::NodeHandle n_;

		action_client *ac1_;
		action_client *ac2_; 

		complex_communication_action::BoardGoal goal;

		//Publisher
		ros::Publisher pub_;

	    // Random variables
		char final_board_[9];
		int count_;

		// Random functions
		void initBoard		(void);
		void initGame		(void);
		void print			(char board[]);
		void announce		(char board[]);
		void nodeShutdown	(void);
		void callPlayer		(action_client *ac, int turn);
		int  checkWin		(char board[]);

	public:
		Server 				(void);
		~Server 			(void);
};

#endif // SERVER_H