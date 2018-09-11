#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ras_lab1_msgs/ADConverter.h"
#include <math.h>

# define alpha -0.01

double dis_sensor1;
double dis_sensor2;

double v = 0.2;
double w = 0;

void adcCallback(const ras_lab1_msgs::ADConverter::ConstPtr& msg);
void set_w(geometry_msgs::Twist& msg);


int main(int argc, char **argv){

    ros::init(argc, argv, "wall_following_controller");
    ros::NodeHandle node_wfc;
    
    ros::Publisher pub_Twist = node_wfc.advertise<geometry_msgs::Twist>("/motor_controller/twist", 1);
    ros::Subscriber sub_dis = node_wfc.subscribe("/kobuki/adc", 10, adcCallback);
    ros::Rate loop_rate(10);

    geometry_msgs::Twist msg_Twist;

    msg_Twist.linear.x = v;
    msg_Twist.linear.y = 0;
    msg_Twist.linear.z = 0;
    msg_Twist.angular.x = 0;
    msg_Twist.angular.y = 0;
    // msg_Twist.angular.z = w;

    while (ros::ok()){
        set_w(msg_Twist);

        pub_Twist.publish(msg_Twist);
        
        ros::spinOnce();
        loop_rate.sleep();
    }
}

void adcCallback(const ras_lab1_msgs::ADConverter::ConstPtr& msg){
    dis_sensor1 = msg->ch1;
    dis_sensor2 = msg->ch2;
    ROS_INFO("d1: [%d], d2: [%d]", dis_sensor1, dis_sensor2);
}

void set_w(geometry_msgs::Twist& msg){
    msg.angular.z =  alpha * (dis_sensor1 - dis_sensor2);
    ROS_INFO("w: [%f]", msg.angular.z);
}
