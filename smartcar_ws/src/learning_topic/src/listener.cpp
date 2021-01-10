#include "ros/ros.h"
#include <sensor_msgs/LaserScan.h>

#include <iostream>

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    std::cout << std::endl << "START" << std::endl;
    for(int i=0; i < 360; i++) {
        std::cout << msg-> ranges[i];
        if(i%10 ==0 )
            std::cout << std::endl;
    }
    std::cout << std::endl << "END"<<std::endl;

    // std::cout << msg -> ranges <<std::endl;
    
    // std::cout << msg -> intensities <<std::stl;

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");
    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("scan_1",1000,chatterCallback);
    ros::spin();

    return 0;
}