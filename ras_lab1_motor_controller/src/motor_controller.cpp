#include "ros/ros.h"
#include "ras_lab1_msgs/PWM.h"
#include "ras_lab1_msgs/Encoders.h"
#include "geometry_msgs/Twist.h"
#include <math.h>

#define TICKS_PER_REV 360
#define CONTROL_FREQUENCY 10
#define WHEEL_RADIUS 0.0352
#define BASE 0.23
#define PI M_PI
#define ALPHA 1
#define BETA 3

double delta_encoder1; // left
double delta_encoder2; // right
double v_desired;
double w_desired;
double estimated_w_l;
double estimated_w_r;
double desired_w_l;
double desired_w_r;
double int_error_l = 0;
double int_error_r = 0;


void encoderCallback(const ras_lab1_msgs::Encoders::ConstPtr& msg);
void twistCallback(const geometry_msgs::Twist::ConstPtr& msg);
void estimated_w();
void desired_w();
void set_PWM(ras_lab1_msgs::PWM& msg);

int main(int argc, char **argv){
    

    ros::init(argc, argv, "motor_controller");
    
    ros::NodeHandle node;   
    ros::Rate loop_rate(10);

    // Publisher and Subscriber
    ros::Publisher pub_pwm = node.advertise<ras_lab1_msgs::PWM>("/kobuki/pwm", 1);
    ros::Subscriber sub_enc = node.subscribe("/kobuki/encoders", 1, encoderCallback);
    ros::Subscriber sub_twist = node.subscribe("/motor_controller/twist", 1, twistCallback);

    // Control
    ras_lab1_msgs::PWM msg_pwm;
    
    while (ros::ok()){
        estimated_w();
        desired_w();
        set_PWM(msg_pwm);
        
        pub_pwm.publish(msg_pwm);
        ros::spinOnce();
        loop_rate.sleep();
    }
}

void encoderCallback(const ras_lab1_msgs::Encoders::ConstPtr& msg){
    delta_encoder1 = double(msg->delta_encoder1);
    delta_encoder2 = double(msg->delta_encoder2);
    ROS_INFO("L: [%f], R: [%f]", delta_encoder1, delta_encoder2);
}

void twistCallback(const geometry_msgs::Twist::ConstPtr& msg){
    v_desired = msg->linear.x;
    w_desired = msg->angular.z;
    ROS_INFO("v: [%f], z: [%f]", v_desired, w_desired);
}

void estimated_w() {
	estimated_w_l = (delta_encoder1 * 2 * PI * CONTROL_FREQUENCY) / TICKS_PER_REV;
	estimated_w_r = (delta_encoder2 * 2 * PI * CONTROL_FREQUENCY) / TICKS_PER_REV;
    ROS_INFO("w_es_l: [%f], w_es_r: [%f]", estimated_w_l, estimated_w_r);
}

void desired_w() {
	desired_w_l = (v_desired - w_desired * (BASE / 2)) / WHEEL_RADIUS;
	desired_w_r = (v_desired + w_desired * (BASE / 2)) / WHEEL_RADIUS;
    ROS_INFO("w_de_l: [%f], w_ds_r: [%f]", desired_w_l, desired_w_r);
}

void set_PWM(ras_lab1_msgs::PWM& msg){
	double error_l = desired_w_l - estimated_w_l;
	int_error_l += error_l / CONTROL_FREQUENCY;
	msg.PWM1 = int (ALPHA * error_l + BETA * int_error_l);
	
	double error_r = desired_w_r - estimated_w_r;
	int_error_r += error_r / CONTROL_FREQUENCY;
	msg.PWM2 = int (ALPHA * error_r + BETA * int_error_r);
    ROS_INFO("pwm1: [%d], pwm2: [%d]", msg.PWM1, msg.PWM2);
}
