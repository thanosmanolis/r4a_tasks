#include "server.h"

/*
*********************
*	 Constructor    *	
*********************
*/

Server::Server(void)
{
	ac1_ = new action_client("player_1", true);
  	ac2_ = new action_client("player_2", true);

	pub_ = n_.advertise<complex_communication_action::Terminate>("/terminate", 1000, true);

	ROS_INFO("Waiting for players to start.");
	
	// wait for the action server to start
	ac1_->waitForServer();
	ac2_->waitForServer();

	ROS_INFO("Players started.");

	initBoard();
	initGame();

	ROS_INFO("[Server] Node initialised");
}

/*
********************
*	 Destructor    *	
********************
*/

Server::~Server(void)
{
	ROS_INFO("[Server] Node destroyed");
}

/*
**************************
*    Initialize board    *	
**************************
*/

void Server::initBoard(void)
{
	complex_communication_action::Terminate msg;
	msg.terminate = 0;
	pub_.publish(msg);	

	for(int i=0; i<9; i++)
	{
		final_board_[i] = ' ';
		goal.board[i] = ' ';
	}

	print(final_board_);

	count_ = 0;
}

/*
*************************
*    Initialize game    *	
*************************
*/

void Server::initGame(void)
{
	while(checkWin(final_board_) == 0)
	{
		if(count_%2==0)
		{
			callPlayer(ac1_, 1);
		}
		else
		{	
			callPlayer(ac2_, 2);
		}
		ros::Duration(1.0).sleep();

		print(final_board_);
	}

	announce(final_board_);
	nodeShutdown();
}

/*
*********************************************
*	 The process of each player's action    *	
*********************************************
*/	

void Server::callPlayer(action_client *ac, int turn)
{
	ac->sendGoal(goal);
	bool finished_before_timeout = ac->waitForResult();
	if (finished_before_timeout)
	{
		actionlib::SimpleClientGoalState state = ac->getState();
		ROS_INFO("Action of player %d finished: %s", turn, state.toString().c_str());

		const complex_communication_action::BoardResult::ConstPtr& result = ac->getResult();
		ROS_INFO("Result is: %d", result->x);
		
		if(turn == 1)
			goal.board[result->x] = 'X';
		else
			goal.board[result->x] = 'O';

		final_board_[result->x] = goal.board[result->x];
    }

	count_++;
}

/*
***********************************************
*    Announce the winner (if there is one)    *	
***********************************************
*/

void Server::announce(char board[])
{
	if(checkWin(board)==1)
	{
		ROS_INFO("Player 1 wins");
	}
	else if(checkWin(board)==2)
	{
		ROS_INFO("Player 2 wins");
	}
	else
	{
		ROS_INFO("It's a tie");
	}
}

/*
********************************
*	 Properly print a board    *	
********************************
*/

void Server::print(char board[])
{
	cout << "=================" << endl;
	
	for(int j=0;j<9;j++)
	{
		
		cout << "|| " << board[j] << " ";
		if(j==2 || j==5 || j==8)
		{
			cout << "||    \n";
		}
	}

	cout << "=================" << endl;
}

/*
******************************************************
*	 Shut down server and players if game is over    *	
******************************************************
*/
void Server::nodeShutdown(void) 
{
  ROS_INFO("Players and then server must shut down");
  
  complex_communication_action::Terminate msg;
  msg.terminate = 1;
  pub_.publish(msg);

  ros::shutdown();
}

/*
***********************************
*	 Check if the game is over    *	
***********************************
*/

int Server::checkWin(char board[])
{
	if (board[0] == board[1]  && board[1] == board[2] && board[0] != ' ')
	{	
		if ( board[0] == 'X' )			
		{
			return 1;
		}
		else if(board[0] == 'O')
		{
			return 2; 
		}
	}		
	else if (board[3] == board[4]  && board[4] == board[5] && board[3] != ' ')
	{	
		if ( board[3] == 'X' )			
		{
			return 1;
		}
		else if(board[3] == 'O')
		{
			return 2; 
		}
	}
	else if (board[6] == board[7]  && board[7] == board[8] && board[6] != ' ')
	{	
		if ( board[6] == 'X' )			
		{
			return 1;
		}
		else if(board[6] == 'O')
		{
			return 2; 
		} 
	}
	else if (board[0] == board[3]  && board[3] == board[6] && board[0] != ' ')
	{	
		if ( board[0] == 'X' )			
		{
			return 1;
		}
		else if(board[0] == 'O')
		{
			return 2; 
		} 
	}
	else if (board[1] == board[4]  && board[4] == board[7] && board[1] != ' ')
	{	
		if ( board[1] == 'X' )			
		{
			return 1;
		}
		else if(board[1] == 'O')
		{
			return 2; 
		} 
	}
    else if (board[2] == board[5]  && board[5] == board[8] && board[2] != ' ')
	{	
		if(board[2] == 'X' )			
		{
			return 1;
		}
		else if(board[2] == 'O')
		{
			return 2; 
		} 
	}
	else if (board[0] == board[4]  && board[4] == board[8] && board[0] != ' ')
	{	
		if(board[0] == 'X')			
		{
			return 1;
		}
		else if(board[0] == 'O')
		{
			return 2; 
		} 
	}
	else if (board[2] == board[4]  && board[4] == board[6] && board[2] != ' ')
	{	
		if( board[2] == 'X' )			
		{
			return 1;
		}
		else if(board[2] == 'O')
		{
			return 2; 
		} 
	}
	else
	{	
		int flag = -1;
		for(int i=0; i<9; i++)
		{
			if(board[i] == ' ')
			{
				flag = 0;
				break;
			} 
		}
		return flag;
	}	
}