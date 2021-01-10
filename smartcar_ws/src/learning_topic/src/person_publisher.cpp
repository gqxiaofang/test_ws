/**
 * 该例程将发布/person_info话题，自定义消息类型learning_topic::Person
 */
 
#include <ros/ros.h>
// #include "learning_topic/Person.h"
#include "cotek_msgs/move_cmd.h"

int main(int argc, char **argv)
{
    // ROS节点初始化
    ros::init(argc, argv, "person_publisher");

    // 创建节点句柄
    ros::NodeHandle n;

    // 创建一个Publisher，发布名为/person_info的topic，消息类型为learning_topic::Person，队列长度10
    // ros::Publisher person_info_pub = n.advertise<learning_topic::Person>("/person_info", 10);

    //cotek
    ros::Publisher cmd_vel_pub;
    cmd_vel_pub = n.advertise<cotek_msgs::move_cmd>("move_cmd", 10);

    // 设置循环的频率
    ros::Rate loop_rate(1);

    int count = 0;
    while (ros::ok())
    {
        // 初始化learning_topic::Person类型的消息
    	// learning_topic::Person person_msg;
		// person_msg.name = "Tom";
		// person_msg.age  = 18;
		// person_msg.sex  = learning_topic::Person::male;
        // person_msg.control_speed = 0.0;
        // person_msg.control_turn = 0.1;
        // 发布消息
		// person_info_pub.publish(person_msg);

        //cotek
        cotek_msgs::move_cmd msg;
        msg.cmd_velocity = 0.0;
        msg.cmd_omega = 0.2;

       	// ROS_INFO("Publish Person Info: control_speed:%f  control_turn:%f", 
				//   person_msg.control_speed, person_msg.control_turn);
        ROS_INFO("Publish Person Info: cmd_velocity:%f  cmd_omega:%f", 
				  msg.cmd_velocity, msg.cmd_omega);          


        // 按照循环频率延时
        loop_rate.sleep();
    }

    return 0;
}
