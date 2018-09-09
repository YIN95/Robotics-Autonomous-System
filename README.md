# Robotics-Autonomous-System
Course: Robotics and Autonomous System

## Lab1 
The assignment is based on a simulated Kobuki robot.  
The final goal of the programming assignment consists in controlling 
a simulated two-wheeled differential drive robot Kobuki and make it 
follow a wall by using readings from distance sensors mounted on the robot. 

### Task1: writing an open loop motor controller  
Coding an open-loop motor controller for the Kobuki.   
Write a C++ node called open_loop_controller which publishes full power commands (PWM = 255) to 
the DC motors through the /kobuki/pwm topic for both of the wheels every 100 milliseconds.

### Task2: writing a motor controller with encoder feedback  
Coding a closed-loop motor controller using encoder feedback.  

### Task3: writing a cartesian controller 
Coding a cartesian controller for a circle trajectory.    


### Task4: writing a wall following controller  
Coding a wall-following controller using also measurements from the distance sensors.  
