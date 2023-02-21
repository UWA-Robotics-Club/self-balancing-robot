---
layout: default
title: Accelerometer and Gyroscope
nav_order: 4
#parent: ..
#has_children: ...
---

# Accelerometer and Gyroscope
{: .no_toc }

<details open markdown="block">
  <summary>
    Table of contents
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

## The MPU6050
In this project, we will be using the MPU6050 to measure the robot's orientation and movement in real time. The MPU6050 is a small, low-cost sensor module that contains both an accelerometer and a gyroscope. The accelerometer in the MPU6050 measures acceleration in 3 dimensions (x, y and z), while the gyroscope measure angular velocity around those same dimensions. For this project, we will only be measuring the angular velocity.

![3 axes on MPU6050](http://127.0.0.1:4000/assets/accelerometer_and_gyroscope/mpu6050_axes.png)



### MPU6050 Pinout 
In this self-balancing robot, we will only be using the VCC, GND, SCL, SDA, and INT pins.

![MPU6050 pinout diagram](http://127.0.0.1:4000/assets/accelerometer_and_gyroscope/mpu6050_pinout.png)



| Pin  | Function | Connections |
| :--- | :---     | :---        |
| VCC | To supply power to the module | Connected to 5V or 3V3 volts on the Arduino Nano |
| GND | Common ground pin | Connected to GND on the Arduino Nano |
| SCL | 


![MPU6050 connections](http://127.0.0.1:4000/assets/accelerometer_and_gyroscope/mpu6050_connections.png)


## Code???
TO DO

- clean up arduino code i have already written
- give credit to those who actually wrote it lmao

### Libraries??
- list libraries used
- tutorial on how to download them 
- and verify that they installed (attempt to compile)

### Calibrating the MPU6050
- code from website

### Reading the Angle of Inclination
- my code which i wrote (adapted from website)
- 


the end??



If you would like to know more about the MPU6050 click here!

https://lastminuteengineers.com/mpu6050-accel-gyro-arduino-tutorial/