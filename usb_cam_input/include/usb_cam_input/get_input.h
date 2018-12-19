#ifndef GET_INPUT_H
#define GET_INPUT_H

#include <ros/ros.h>
#include <sensor_msgs/Image.h>

namespace usb_cam_input
{
class GetInput
{
	private:
		ros::NodeHandle nh_;

		//! ROS Subscriber
		ros::Subscriber sub_;

		//! Random functions
		void inputCallback(const sensor_msgs::Image::ConstPtr &msg);

	public:
		GetInput 	(void);
		~GetInput 	(void);
};
}

#endif