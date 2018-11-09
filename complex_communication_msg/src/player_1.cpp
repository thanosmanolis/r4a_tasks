#include "player.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "player_1");
	Player player1(1);
	ros::spin();

	return 0;
}