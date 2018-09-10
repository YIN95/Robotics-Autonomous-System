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
The DC motors simulated in this lab have 360 ticks per revolution (1 revolution = 360 degrees of rotation = 2*pi radians of rotation).   
Each control cycle is 100 ms long (10 Hz control). 

**For this assignment, implement a P-controller for each of the motors, also a PI-controller should work much better*

### Task3: writing a cartesian controller 
Coding a cartesian controller for a circle trajectory.    


### Task4: writing a wall following controller  
Coding a wall-following controller using also measurements from the distance sensors.  
