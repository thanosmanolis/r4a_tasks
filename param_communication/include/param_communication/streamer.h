#ifndef PARAM_COMMUNICATION_STREAMER_H
#define PARAM_COMMUNICATION_STREAMER_H

#include <ros/ros.h>
#include <ros/time.h>
#include <param_communication/Num.h>

namespace param_communication
{
class Streamer
{
    private:
        ros::NodeHandle nh_;
        param_communication::Num msg_;

        //! Message publisher.
        ros::Publisher pub_;

        //! Publisher's frequency as a static parameter
        double rand_number_freq_;

        //! Random Functions
        void updateParameters       (void);
        void publishRandomNumbers   (void);
        double getRandNumberFreq    (void);
        void setRandNumberFreq      (double freq);

    public:
        //! Constructor.
        explicit Streamer   (ros::NodeHandle nh);
        ~Streamer           (void);
};
}

#endif  // PARAM_COMMUNICATION_STREAMER_H