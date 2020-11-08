#include <sstream>

#include "cotek_msgs/move_cmd.h"
#include "ros/ros.h"

int main(int argc, char **argv) {
  ros::init(argc, argv, "talker");
  ros::NodeHandle nh;
  ros::Publisher cmd_vel_pub;
  cmd_vel_pub = nh.advertise<cotek_msgs::move_cmd>("move_cmd", 10);

  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok()) {
    cotek_msgs::move_cmd msg;

    msg.cmd_velocity = 0.05;
    msg.cmd_omega = 0.1;
    cmd_vel_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}
