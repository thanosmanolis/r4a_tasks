#include <obst_avoid_robot/avoid_obstacles.h>

namespace obst_avoid_robot
{

/*
*********************
*    Constructor    * 
*********************
*/

AvoidObstacles::AvoidObstacles(ros::NodeHandle nh): nh_(nh)
{
	sub_ = nh_.subscribe("/robot0/laser_0", 10, &AvoidObstacles::laserCallback, this);
	pub_ = nh_.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 10);
}

/*
********************
*    Destructor    *  
********************
*/

AvoidObstacles::~AvoidObstacles(void)
{
    ROS_INFO("[AvoidObstacles] Node destroyed.");
}

/*
*************************************
*    Get data from laser sensor.    *  
*************************************
*/

void AvoidObstacles::laserCallback(const sensor_msgs::LaserScan::ConstPtr &msg)
{
	float linear = 0;
	float angular = 0;
	
	for(int i=0; i<msg->ranges.size(); i++)
    {
      float real_dist = msg->ranges[i];
      linear -= cos(msg->angle_min + i*msg->angle_increment) / (real_dist);
      angular -= sin(msg->angle_min + i*msg->angle_increment) / (0.5*real_dist);
    }
    
    linear = linear / msg->ranges.size();
    angular = angular / msg->ranges.size();
    
    if(linear > 0.4)
    {
      linear = 0.4;
    }
    else if(linear < -0.4)
    {
      linear = -0.4;
    }

    msg_speeds_.linear.x = 0.4 + linear;
    msg_speeds_.angular.z = angular;
    pub_.publish(msg_speeds_);
}

}