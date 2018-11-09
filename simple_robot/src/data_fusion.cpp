#include <data_fusion.h>

/*
*********************
*	 Constructor    *	
*********************
*/

DataFusion::DataFusion(int threshold): 
	threshold_(threshold)
{
	pub_ = n_.advertise<simple_robot::VictimFound>("/data_fusion/victim_found", 1000, true);

	sub_ = n_.subscribe("/sensors/temperature", 1000, &DataFusion::dataCallBack, this);

	ROS_INFO("***********************************");
	ROS_INFO("[data_fusion] Node Initialized.   *");
	ROS_INFO("***********************************");
}

/*
********************
*	 Destructor    *	
********************
*/

DataFusion::~DataFusion(void)
{
	ROS_INFO("[data_fusion] Node Destroyed.");
}

/*
****************************************************************
*	 Retrieve the message from the sensor and send a victim    *
*	 alert if the pose's temperature is over threshold.        *
****************************************************************
*/

void DataFusion::dataCallBack(const simple_robot::TemperatureReading::ConstPtr& msg)
{
	if(msg->temperature >= threshold_)
	{
		ROS_INFO("************************************");
		ROS_INFO("Victim Alert. Temperature is: %d   *", msg->temperature);
		ROS_INFO("************************************");

		pub_.publish(msg_);
	}
}


/*
***********************
*	 Main Function    *	
***********************
*/

int main(int argc, char **argv)		
{
	ros::init(argc, argv, "data_fusion");
	DataFusion victim(37);
	ros::spin();

	return 0;
}