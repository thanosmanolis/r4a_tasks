#include "player.h"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "player_2");
	Player player2(2);
	ros::spin();

	return 0;
}