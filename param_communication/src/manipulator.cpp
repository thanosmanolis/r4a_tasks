#include <param_communication/manipulator.h>

namespace param_communication
{

/*
*********************
*    Constructor    * 
*********************
*/

Manipulator::Manipulator(ros::NodeHandle nh): 
    nh_(nh), 
    power_(2)
{
    setUpServer();
    initParams();

    sub_ = nh.subscribe("/task5/numbers", 10, &Manipulator::messageCallback, this);
}

/*
********************
*    Destructor    *  
********************
*/

Manipulator::~Manipulator(void)
{
    ROS_INFO("[Manipulator] Node destroyed.");
}

/*
***********************************************************
*    Retrieves random numbers (x) and prints x^power_.    *
***********************************************************
*/

void Manipulator::messageCallback(const param_communication::Num::ConstPtr &msg)
{
    ROS_INFO("[Manipulator] x ^ power = %d", (int) pow(msg->num, power_));
}

/*
**********************************************
*    Set up a dynamic reconfigure server.    * 
**********************************************
*/

void Manipulator::setUpServer(void)
{
    dynamic_reconfigure::Server<param_communication::paramsConfig>::CallbackType cb;
    cb = boost::bind(&Manipulator::configCallback, this, _1, _2);
    dr_srv_.setCallback(cb);
}

/*
**************************************************************************************
*    Initialize parameters using a private node handle so that multiple instances    *
*    of the node can be run simultaneously while using different parameters.         * 
**************************************************************************************
*/

void Manipulator::initParams(void)
{
    ros::NodeHandle pnh("~");
    pnh.param("power", power_, power_);
}

/*
***********************************************************
*    Callback function for dynamic reconfigure server.    * 
***********************************************************
*/

void Manipulator::configCallback(param_communication::paramsConfig &config, uint32_t level __attribute__((unused)))
{
    // Set class variables to new values. They should match what is input at the dynamic reconfigure GUI.
    power_ = config.power;
}

}