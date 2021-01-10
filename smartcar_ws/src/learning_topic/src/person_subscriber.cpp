/**
 * 该例程将订阅/person_info话题，自定义消息类型learning_topic::Person
 */
 
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include "cotek_msgs/move_cmd.h"
#include <iostream>
#include<fstream>

#define SIZEOF(arr) (sizeof(arr)/sizeof(arr[0]))

void print_arr(int* arr);
void print_arr(float* arr);
int* add_num(int* arr, int num);
float* add_num(float* arr, float num);
int get_len(int* arr);
int get_len(float* arr);
int* delete_num(int* arr);
float* delete_num(float* arr);

int MAX_sub(float* arr, int low, int up);


class SubscribeAndPublish //创建一个“类”，名为SubscribeAndPublish
{
public: 
    SubscribeAndPublish() 
    {
        max_start = 0 ;
        max_end = 0;
        start = 0;
        end = 0;
        LEN = 630;
        flag = 0;
        last_flag = 0;
        angel = 0.0;
        //Topic you want to publish
        pub = n.advertise<cotek_msgs::move_cmd>("move_cmd", 10);
        //Topic you want to subscribe
        sub = n.subscribe("scan_2", 1000, &SubscribeAndPublish::callback, this);
    }
    void callback(const sensor_msgs::LaserScan::ConstPtr& input) 
    {
        for(int i=525,j=0; i < 3675; i+=5,j++) {
            j = 0;
            std::cout << input -> ranges[i] << " ";
            laser[i] = input -> ranges[i];
            if(i%10 ==0 )
            std::cout << std::endl;
            if(input->ranges[i] > 0.80)
            {
                flag = 1;
                if(last_flag == 0)
                {  
                    if((end-start)>(max_end-max_start))
                    {
                        max_start = start;
                        max_end = start;
                    }
                    max_start = start;
                    max_end = end;     
                    start = j; // #include “sstream”
                    end = j;
                }
                if(start > end)
                {
                    end = start;
                }
            }else
            {
                flag = 0;
            }
            last_flag = flag;
        }
        
        angel = (float)(max_start + max_end)/2.3/2 ;
        max_start = 0;
        max_end = 0;
        std::cout << "angel:" << angel << std::endl;
        cotek_msgs::move_cmd msg;
        msg.cmd_velocity = 0.0;
        msg.cmd_omega = 0.0;
        pub.publish(msg);
        ros::spinOnce();
    }
// private: //private里面写的是属性
    ros::NodeHandle n;
    ros::Publisher pub;
    ros::Subscriber sub;
    float laser[650];
    int LEN;
    int max_start;
    int max_end;
    int start;
    int end;
    int flag;
    int last_flag;
    float angel;
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "smart_car");
    SubscribeAndPublish SAPObject;
    ros::spin();
    return 0;
}
/***********************************************
模拟python append
************************************************/
int* add_num(int* arr, int num)
{
    int i = 0;
    if (arr == NULL)
    {
        arr = new int [2];
        arr[0] = num;
        arr[1] = -1;
        return arr;
    }
    int len = get_len(arr);
    int* arr2 = new int [len + 1];
    for (i = 0; i < len; i++)
    {
        arr2[i] = arr[i];
    }
    arr2[i-1] = num;
    arr2[i] = -1;
    delete []arr;
    return arr2;
}
float* add_num(float* arr, float num)
{
    int i = 0;
    if (arr == NULL)
    {
        arr = new float[2];
        arr[0] = num;
        arr[1] = -1;
        return arr;
    }
    int len = get_len(arr);
    float* arr2 = new float[len + 1];
    for (i = 0; i < len; i++)
    {
        arr2[i] = arr[i];
    }
    arr2[i - 1] = num;
    arr2[i] = -1;
    delete[]arr;
    return arr2;
}
/***********************************************
检索坏值
************************************************/
void print_arr(int* arr)
{
    if (arr == NULL)
        return;
    int len = get_len(arr);
    for (int i = 0; i < len; i++)
        std::cout << arr[i] << " " << std::endl;
}
void print_arr(float* arr)
{
    if (arr == NULL)
        return;
    int len = get_len(arr);
    for (int i = 0; i < len; i++)
        std::cout << arr[i] << " " << std::endl;
}
/***********************************************
获取长度
************************************************/
int get_len(int* arr)
{
    if (arr == NULL)
        return 0;
    int len = 0;
    for (int i = 0; 1; i++)
    {
        len++;
        if (arr[i] < 0)
            break;
    }
    return len;
}
int get_len(float* arr)
{
    if (arr == NULL)
        return 0;
    int len = 0;
    for (int i = 0; 1; i++)
    {
        len++;
        if (arr[i] < 0.0f)
            break;
    }
    return len;
}
/***********************************************
删除尾部
************************************************/
int* delete_num(int* arr)
{
    if (arr == NULL)
        return NULL;
    int len = get_len(arr);
    int* arr2 = new int[len - 1];
    for (int i = 0; i < len - 1; i++)
        arr2[i] = arr[i];
    arr2[len - 2] = -1;
    delete[]arr;
    return arr2;
}
float* delete_num(float* arr)
{
    if (arr == NULL)
        return NULL;
    int len = get_len(arr);
    float* arr2 = new float[len - 1];
    for (int i = 0; i < len - 1; i++)
        arr2[i] = arr[i];
    arr2[len - 2] = -1;
    delete[]arr;
    return arr2;
}
int MAX_sub(float* arr,int low,int up)
{
    if(arr == NULL)
    {
        std::cout<<"error"<<std::endl;
        return 0;
    }
    float max = 0.0f;
    int sub = 0;
    for (int i = low; i < up; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
            sub = i;
        }
    }
    return sub;

}

