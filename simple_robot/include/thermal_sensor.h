#ifndef THERMAL_SENSOR_H
#define THERMAL_SENSOR_H

#include "ros/ros.h"
#include <simple_robot/TemperatureReading.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

using namespace std;

class ThermalSensor
{
	private:
		ros::NodeHandle n_;
		simple_robot::TemperatureReading msg_;

		//Publisher
		ros::Publisher pub_;

		// Random functions
		void createRandomValue	(void);

	public:
		ThermalSensor 	(void);
		~ThermalSensor 	(void);
};

#endif // THERMAL_SENSOR_H