#include <obst_avoid_robot/robot_tf_listener.h>

namespace obst_avoid_robot
{

/*
*********************
*    Constructor    * 
*********************
*/

RobotTfListener::RobotTfListener(ros::NodeHandle nh): nh_(nh)
{
    pub_marker_vel_ = nh_.advertise<geometry_msgs::Twist>("/robot0/cmd_vel", 10);

    ros::service::waitForService("spawn");
    ros::ServiceClient add_turtle = nh_.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);

    followRobot();
}

/*
********************
*    Destructor    * 
********************
*/

RobotTfListener::~RobotTfListener(void)
{
    ROS_INFO("[robot_tf_listener] Node destroyed.");
}

/*
***********************************
*    Make marker follow robot.    * 
***********************************
*/

void RobotTfListener::followRobot(void)
{
    ros::Rate rate(10.0);
    while (nh_.ok())
    {
        try
        {
            listener_.lookupTransform("/robot0", "/map", ros::Time(0), transform_);
        }
        catch (tf::TransformException &ex) 
        {
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
            continue;
        }

        vel_msg_.angular.z = 4.0 * atan2(transform_.getOrigin().y(),
                                         transform_.getOrigin().x());
        vel_msg_.linear.x = 0.5 * sqrt(pow(transform_.getOrigin().x(), 2) +
                                       pow(transform_.getOrigin().y(), 2));
        pub_marker_vel_.publish(vel_msg_);

        rate.sleep();
    }
}

}