#include <usb_cam_input/get_input.h>

namespace usb_cam_input
{

/*
*********************
*    Constructor    * 
*********************
*/
GetInput::GetInput(void)
{
	sub_ = nh_.subscribe("yolo", 10, &GetInput::inputCallback, this);
}

/*
********************
*    Destructor    *  
********************
*/

GetInput::~GetInput(void)
{
    ROS_INFO("[get_input] Node destroyed.");
}

/*
***********************************
*    Callback to get te input.    *  
***********************************
*/
void GetInput::inputCallback(const sensor_msgs::Image::ConstPtr &msg)
{
	ROS_INFO("height x width : %d x %d", msg->height, msg->width);
}

}
