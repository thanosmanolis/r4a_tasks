#include "server.h" 

int main(int argc, char **argv)		
{
	ros::init(argc, argv, "server_node");
	Server server;
	ros::spin();

	return 0;
}	