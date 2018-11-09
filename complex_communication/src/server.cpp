#include "ros/ros.h"
#include "complex_communication/Move.h"
#include <cstdlib>
#include <iostream>	

using namespace std;

int Checkwin(char board[]);
void Print(char board[]);

int main(int argc, char **argv)		
{
	ros::init(argc, argv, "server");
	ros::NodeHandle n;
	
	ros::ServiceClient client1 = n.serviceClient<complex_communication::Move>("move1");
	ros::ServiceClient client2 = n.serviceClient<complex_communication::Move>("move2");
	ros::Rate loop_rate(1);

	char board[9];
	for(int i=0; i<9; i++)
	{
		board[i] = ' ';	
	} 
	
	Print(board);
	ROS_INFO("Let's start");

	int count = 0;
	while(Checkwin(board) == 0 && ros::ok()) 
	{
		complex_communication::Move srv;
		
		for(int i=0;i<9;i++)
		{
			srv.request.old_board[i] = board[i];
		}
		
		
		if(count%2==0 && client1.call(srv))
		{
			for(int i=0;i<9;i++)
			{
				board[i] = srv.response.new_board[i];
			}
		}
		else if(client2.call(srv))
		{	
			for(int i=0;i<9;i++)
			{
				board[i] = srv.response.new_board[i];
			}
		}

		Print(board);
		
		ros::spinOnce();
		loop_rate.sleep();
		count++;
	}

	if(Checkwin(board)==1)
	{
		ROS_INFO("Player 1 wins");
	}
	else if(Checkwin(board)==2)
	{
		ROS_INFO("Player 2 wins");
	}
	else
	{
		ROS_INFO("It's a tie");
	}

	return 0;
}

void Print(char board[])
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

int Checkwin(char board[])
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