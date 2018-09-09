#include "ros/ros.h"
#include "ras_lab1_msgs/PWM.h"

int main(int argc, char **argv){
    ros::init(argc, argv, "open_loop_controller");
    ros::NodeHandle pwm_n;

    ros::Publisher pwm_pub = pwm_n.advertise<ras_lab1_msgs::PWM>("/kobuki/pwm", 100);
    ros::Rate loop_rate(10);

    ras_lab1_msgs::PWM pwm_msg;

    pwm_msg.PWM1 = 255;
    pwm_msg.PWM2 = 255;

    while (ros::ok()){
        pwm_pub.publish(pwm_msg);
        ros::spinOnce();
        loop_rate.sleep();
    }
}