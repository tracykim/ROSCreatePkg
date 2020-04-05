#include "ros/ros.h"
#include "std_msgs/String.h"//要和订阅的消息类型所匹配

void chatterCallback(const std_msgs::String::ConstPtr& msg)//回调函数
{
    ROS_INFO("I heard: [%s]", msg->data.c_str());
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "listener");//初始化ros，向master注册一个叫“listener”的节点

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    //订阅者向master注册自己需要订阅的话题"chatter"，消息队列大小是1000，chatterCallback是回调函数
    //回调函数的意义是，当订阅者从自己所订阅的话题上接收到消息，回调函数自动执行

    ros::spin();//因为不在while循环体中，所以它要不断执行，而不是用spinOnce()，只执行一次

    return 0;
}
