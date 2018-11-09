#include <param_communication/streamer.h>

namespace param_communication
{

/*
*********************
*    Constructor    * 
*********************
*/

Streamer::Streamer(ros::NodeHandle nh) : nh_(nh)
{
	updateParameters();
	publishRandomNumbers();
}

/*
********************
*    Destructor    *  
********************
*/

Streamer::~Streamer(void)
{
  	ROS_INFO("[Streamer] Node destroyed.");
}

/*
********************************************
*    Reads the parameters from the yaml    * 
*    file and fills the structure.         *  
********************************************
*/

void Streamer::updateParameters(void)
{ 
	if (nh_.hasParam(ros::this_node::getName() + "/rand_number_freq"))
	{
		nh_.getParam(ros::this_node::getName() + "/rand_number_freq", rand_number_freq_);
	}  
	else 
	{
		ROS_WARN("[Streamer] Parameter rand_number_freq not found.\
			Using Default");
		rand_number_freq_ = 1.0 ;
	}
}

/*
**********************************************
*    Constantly publishes random numbers.    *  
**********************************************
*/

void Streamer::publishRandomNumbers()
{
	pub_ = nh_.advertise<param_communication::Num>("/task5/numbers", 10);

	ros::Rate loop_rate(rand_number_freq_);
	srand(time(NULL));

	while(ros::ok())
	{
		msg_.num = rand()%10;

		ROS_INFO("[Streamer] x = %d", msg_.num);
		pub_.publish(msg_);

		ros::spinOnce();
		loop_rate.sleep();
	}
}

/*
************************************************
*    Setter & Getter for freq static param.    *  
************************************************
*/
void Streamer::setRandNumberFreq(double freq)
{
	rand_number_freq_ = freq;
}

double Streamer::getRandNumberFreq(void)
{
	return rand_number_freq_;
}

}