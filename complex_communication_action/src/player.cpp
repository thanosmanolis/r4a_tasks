#include "player.h"

/*
*********************
*	 Constructor    *	
*********************
*/
		
Player::Player(string name, int turn):
	as_(n_, name, boost::bind(&Player::executeCB, this, _1), false),
	action_name_(name),
	turn_(turn)
{
	as_.start();

	sub_ = n_.subscribe("/terminate", 1000, &Player::nodeShutdown, this);

	ROS_INFO("[Player %d] Node initialized", turn_);
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

void Player::executeCB(const complex_communication_action::BoardGoalConstPtr &goal) 
{ 
	bool success = true;

	ROS_INFO("Action server %d called", turn_);
  	ROS_INFO("Player %d is considering his move", turn_);

	if (as_.isPreemptRequested() || !ros::ok())
	{
		ROS_INFO("%s: Preempted", action_name_.c_str());
		as_.setPreempted();
		success = false;
	}

	srand(time(NULL));
	int j = rand()%9;
	while(goal->board[j] != ' ')
	{
		j = rand()%9;
	}

	result_.x = j;

	ROS_INFO("Player %d 's is move is (%d,%d)", turn_, (result_.x - result_.x % 3) / 3, result_.x % 3);

	if(success)
	  {
	    ROS_INFO("%s: Succeeded", action_name_.c_str());
	    // set the action state to succeeded
	    as_.setSucceeded(result_);
	  }
}

void Player::nodeShutdown(complex_communication_action::Terminate msg) 
{ 
	if(msg.terminate == 1)
	{
		ros::shutdown();
	}
}