#ifndef PLAYER_H
#define PLAYER_H

#include "ros/ros.h"
#include "complex_communication_msg/Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class Player
{
	private:
		ros::NodeHandle n_; 
		complex_communication_msg::Board msg_;

		// Subscribers
		ros::Subscriber sub_;

		// Publishers
		ros::Publisher  pub_;

		// Callbacks
		void playerCallBack(complex_communication_msg::Board msg);

	    // Random variables
		int  turn_;
		char temp_board_[9];
		char move_;

		// Random functions
		void publish(void);
			
	public:
		Player 	(int turn);
		~Player (void);
};

#endif // PLAYER_H