#ifndef SERVER_H
#define SERVER_H

#include "ros/ros.h"
#include "complex_communication_msg/Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Server
{
	private:
		ros::NodeHandle n_; 
		complex_communication_msg::Board msg_;

		// Subscribers
		ros::Subscriber sub_;

		// Publishers
		ros::Publisher pub1_;
		ros::Publisher pub2_;

		// Callbacks
		void serverCallBack(complex_communication_msg::Board msg);

	    // Random variables
		char final_board_[9];
		int count_;

		// Random functions
		void initBoard		(void);
		void print			(char board[]);
		void announce		(char board[]);
		void publish 		(complex_communication_msg::Board msg);
		void gameShutdown	(void);
		int  checkWin		(char board[]);

	public:
		Server 	(void);
		~Server (void);
};

#endif // SERVER_H