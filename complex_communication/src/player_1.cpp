#include "ros/ros.h"
#include "complex_communication/Move.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

bool play(complex_communication::Move::Request  &req,
		  complex_communication::Move::Response &res)
{
	res.new_board = req.old_board;

	srand(time(NULL));
	int i = rand()%9;
	while(req.old_board[i] != ' ')
	{	
		i = rand()%9;
	}
	res.new_board[i] = 'X';
	return true;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "player_1");
	ros::NodeHandle n;

	ros::ServiceServer service = n.advertiseService("move1", play);

	ROS_INFO("Player 1 is ready.");

	ros::spin();

	return 0;
}