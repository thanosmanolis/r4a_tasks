#include <learning_tf/turtle_tf_listener.h>

namespace learning_tf
{

/*
*********************
*    Constructor    * 
*********************
*/

TurtleTfListener::TurtleTfListener(ros::NodeHandle nh): nh_(nh)
{
    spawnTurtle();

    pub_turtle_vel_ = nh_.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

    followTurtle();
}

/*
********************
*    Destructor    * 
********************
*/

TurtleTfListener::~TurtleTfListener(void)
{
    ROS_INFO("[turtle_tf_listener] Node destroyed.");
}

/*
************************
*    Spawn turtle2.    * 
************************
*/

void TurtleTfListener::spawnTurtle(void)
{
    ros::service::waitForService("spawn");
    ros::ServiceClient add_turtle = nh_.serviceClient<turtlesim::Spawn>("spawn");
    turtlesim::Spawn srv;
    add_turtle.call(srv);
}

/*
**********************************************
*    Make turtle2 follow another turtle1.    * 
**********************************************
*/

void TurtleTfListener::followTurtle(void)
{
    ros::Rate rate(10.0);
    while (nh_.ok())
    {
        try
        {
            listener_.lookupTransform("/turtle2", "/carrot1", ros::Time(0), transform_);
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
        pub_turtle_vel_.publish(vel_msg_);

        rate.sleep();
    }
}

}