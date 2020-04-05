#include "ros/ros.h"//ROS程序必备的头文件
#include "std_msgs/String.h"//传递的消息类型
#include "sstream"

int main(int argc, char **argv)//写ROS程序需要加argc,argv，因为init需要传这两个参数
{
    ros::init(argc, argv, "talker");//初始化ros，向master注册一个叫“talker”的节点

    ros::NodeHandle n;//初始化一个句柄，就是将ROS实例化

    ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
    //发布者注册一个叫“chatter”的话题，<消息类型>,1000是消息队列大小
    //消息队列相当于缓存消息，如果处理速度不够快的话消息会被保存在队列中

    ros::Rate loop_rate(10);//执行循环的速率，可以理解为发布消息的频率，单位是Hz

    int count = 0;
    while (ros::ok())//ros::ok()函数用来判断master节点是否正常
    {
        std_msgs::String msg;//声明变量

        std::stringstream ss;
        ss << "hello world " << count++;
        msg.data = ss.str();

        ROS_INFO("%s", msg.data.c_str());//ROS_INFO()可以在终端打印数据

        chatter_pub.publish(msg);//发布该消息

        ros::spinOnce();//动作执行一次
        //ros::spin()是循环执行，在没有while的时候使用

        loop_rate.sleep();//相当于delay函数，因为程序可能不需要0.1s，就是10Hz的频率就可以发送完成，所以sleep()函数可以让程序暂停一会，让消息的发送频率符合10Hz
    }
    return 0;
}
