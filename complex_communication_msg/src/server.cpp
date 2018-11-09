#include "server.h"

/*
*********************
*	 Constructor    *	
*********************
*/

Server::Server(void)
{
	pub1_ = n_.advertise<complex_communication_msg::Board>("/old_board1", 1);
	pub2_ = n_.advertise<complex_communication_msg::Board>("/old_board2", 1);

	sub_ = n_.subscribe("/new_board",1, &Server::serverCallBack, this);
	ros::Duration(0.5).sleep();

	ROS_INFO("[Server] Node initialised");
	initBoard();
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
*****************************************
*    Initialize board and publish it 	*	
*****************************************
*/

void Server::initBoard(void)
{
	count_ = 0;

	msg_.terminate = 0;

	for(int i=0; i<9; i++)
	{
		msg_.board[i] = ' ';
		final_board_[i] = ' ';
	}

	ROS_INFO("[Server] Board initialized");
	print(final_board_);

	pub1_.publish(msg_);
	count_++;
}

/*
******************************************************
*	 Publish the board to the next player's topic	 *	
******************************************************
*/	

void Server::serverCallBack(complex_communication_msg::Board msg)
{
	for(int i=0;i<9;i++)
	{
		final_board_[i] = msg.board[i];
	}

	if(checkWin(final_board_) == 0)
	{		
		print(final_board_);
		publish(msg);
		ros::Duration(1.0).sleep();
	}
	else
	{	
		print(final_board_);
		announce(final_board_);

		ROS_INFO("Players and then server must shut down");
		gameShutdown();
	}
}

/*
************************************
*	 Publish a message function    *	
************************************
*/	

void Server::publish(complex_communication_msg::Board msg)
{
	if(count_%2 == 0)
		{	
			pub1_.publish(msg);
		}
		else
		{	
			pub2_.publish(msg);
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
***********************************
*	 Shut down if game is over    *	
***********************************
*/

void Server::gameShutdown(void)
{
	msg_.terminate = 1;
	pub1_.publish(msg_);
	pub2_.publish(msg_);
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