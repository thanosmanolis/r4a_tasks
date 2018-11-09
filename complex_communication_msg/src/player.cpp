#include "player.h"

/*
*********************
*	 Constructor    *	
*********************
*/
		
Player::Player(int turn):
	turn_(turn)
{
	pub_ = n_.advertise<complex_communication_msg::Board>("/new_board", 1);

	if(turn_ == 1)
	{
		move_ = 'X';
		sub_ = n_.subscribe("/old_board1", 1, &Player::playerCallBack, this);
	}
	else
	{
		move_ = 'O';
		sub_ = n_.subscribe("/old_board2", 1, &Player::playerCallBack, this);
	}

	ROS_INFO("[Player %d] Node initialized", turn);
}

/*
********************
*	 Destructor    *	
********************
*/

Player::~Player(void)
{
	ROS_INFO("[Player %d] Node destroyed", turn_);
}

/*
**********************************************************************
*	 Retrieve the board, make a move, and send the new board back    *	
**********************************************************************
*/

void Player::playerCallBack(complex_communication_msg::Board msg) 
{ 
	if(msg.terminate == 1)
	{
		ros::shutdown();
	}

	for(int i=0; i<9; i++)
	{
		temp_board_[i] = msg.board[i];
	}

	srand(time(NULL));
	int j = rand()%9;
	while(temp_board_[j] != ' ')
	{
		j = rand()%9;
	}

	temp_board_[j] = move_;
	publish();
}

void Player::publish(void)
{	
	msg_.terminate = 0;

	for(int i=0; i<9; i++)
	{
		msg_.board[i] = temp_board_[i]; 
	}

	pub_.publish(msg_);
}