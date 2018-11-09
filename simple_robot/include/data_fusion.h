#ifndef DATA_FUSION_H
#define DATA_FUSION_H

#include "ros/ros.h"
#include <simple_robot/TemperatureReading.h>
#include <simple_robot/VictimFound.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

class DataFusion
{
	private:
		ros::NodeHandle n_;
		simple_robot::VictimFound msg_;
		int threshold_;

		//Subscriber
		ros::Subscriber sub_;

		//Publisher
		ros::Publisher pub_;

		// Callbacks
		void dataCallBack(const simple_robot::TemperatureReading::ConstPtr& msg);

	public:
		DataFusion 	 	(int threshold);
		~DataFusion 	(void);
};

#endif // DATA_FUSION_H