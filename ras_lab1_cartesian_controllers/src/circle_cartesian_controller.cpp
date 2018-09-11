#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <math.h>

#define R 0.5
#define T 10

int main(int argc, char **argv){
    double w = 2 * M_PI / T;
    double v = w * R;

    ros::init(argc, argv, "line_cartesian_controller");
    ros::NodeHandle node_cc;
    
    ros::Publisher pub_Twist = node_cc.advertise<geometry_msgs::Twist>("/motor_controller/twist", 1);
    ros::Rate loop_rate(1);

    geometry_msgs::Twist msg_Twist;

    msg_Twist.linear.x = v;
    msg_Twist.linear.y = 0;
    msg_Twist.linear.z = 0;
    msg_Twist.angular.x = 0;
    msg_Twist.angular.y = 0;
    msg_Twist.angular.z = w;

    while (ros::ok()){
        pub_Twist.publish(msg_Twist);
        ros::spinOnce();
        loop_rate.sleep();
    }

}