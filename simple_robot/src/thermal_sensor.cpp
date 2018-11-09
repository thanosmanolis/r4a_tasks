#include <thermal_sensor.h>

/*
*********************
*	 Constructor    *	
*********************
*/

ThermalSensor::ThermalSensor(void)
{
	pub_ = n_.advertise<simple_robot::TemperatureReading>("/sensors/temperature", 1000, true);
	
	ROS_INFO("[thermal_sensor] Node Initialized.");

	createRandomValue();
}

/*
********************
*	 Destructor    *	
********************
*/

ThermalSensor::~ThermalSensor(void)
{
	ROS_INFO("[thermal_sensor] Node Destroyed.");
}

/*
***********************************************************
*			        Simulate the sensor			          *
***********************************************************
*	 Create a random value between [20,40] each second    *
*	 second and post it in the corresponding topic.       *
***********************************************************
*/

void ThermalSensor::createRandomValue(void)
{
	ros::Rate loop_rate(1);
	srand(time(NULL));

	while (ros::ok()) 
	{
		msg_.temperature = rand()%21+20;

		ROS_INFO("***********************************************");
		ROS_INFO("[thermal_sensor] Temperature is: %d Celsius   *", msg_.temperature);
		ROS_INFO("***********************************************");

		pub_.publish(msg_);

		loop_rate.sleep();
	}
}


/*
***********************
*	 Main Function    *	
***********************
*/

int main(int argc, char **argv)		
{
	ros::init(argc, argv, "thermal_sensor");
	ThermalSensor sensor;
	ros::spin();

	return 0;
}