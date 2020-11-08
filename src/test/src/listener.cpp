#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>

#include <sstream>

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    std::cout << msg -> angle_max <<std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("scan_1",1000,chatterCallback);
    ros::spin();

    return 0;
}