#ifndef PARAM_COMMUNICATION_MANIPULATOR_H
#define PARAM_COMMUNICATION_MANIPULATOR_H

// ROS includes.
#include <ros/ros.h>
#include <ros/time.h>

// Custom message includes. Auto-generated from msg/ directory.
#include <param_communication/Num.h>

// Dynamic reconfigure includes.
#include <dynamic_reconfigure/server.h>
// Auto-generated from cfg/ directory.
#include <param_communication/paramsConfig.h>

namespace param_communication
{
class Manipulator
{
 private:
  //! ROS node handle.
  ros::NodeHandle nh_;

  //! Dynamic reconfigure server.
  dynamic_reconfigure::Server<param_communication::paramsConfig> dr_srv_;

  //! ROS Subscriber
  ros::Subscriber sub_;

  //! The power as a dynamic paramater.
  int power_;

  //! Random Functions.
  void setUpServer      (void);
  void initParams       (void);
  void messageCallback  (const param_communication::Num::ConstPtr &msg);
  void configCallback   (param_communication::paramsConfig &config, uint32_t level);

  public:
    //! Constructor.
    explicit Manipulator  (ros::NodeHandle nh);
    ~Manipulator          (void);
};
}

#endif  // PARAM_COMMUNICATION_MANIPULATOR_H
