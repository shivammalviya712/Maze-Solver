# Objective
The robot should be able find its way out of the maze on its own.

# Components
![](images/Image1.png)
- Arduino Uno: 1
- DC Motor: 2
- Motor driver: 1
- Ultrasonic sensor: 3
- Wheel: 2
- Castor: 1
- Chassis: 1
- 9V Battery: 1
- Jumper wire: As required
- Breadboard: 1

After assembling components
![](images/Image2.jpeg)

# Algorithm
There are many algorithms to solve the maze. I have used left wall follower algorithm. This algorithm works if the maze is simply connected. The idea is to keep one hand always in contact with one wall of the maze either left or right. If there is a exit, and maze is simply connected then robot will definitely reach the exit. 

The priority in left wall following algorithm is in the following order: 
- Left 
- Forward
- Right

# Requirement
- PID_v1.h
- Newping.h

# Pictures
![](images/Image3.png)
<p align="center">
  <img src= images/Image4.png>
</p>
