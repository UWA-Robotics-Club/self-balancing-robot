---
layout: default
title: PID Control
nav_order: 6
#parent: ..
#has_children: ...
---

# PID Control
{: .no_toc }

<details open markdown="block">
  <summary>
    Table of contents
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

## Feedback Control
Now that we understand how to read angles from the MPU6050 and control the DC motors using the Arduino Nano, we can integrate these two components in a closed-loop feedback control system to create a self-balancing robot.

The aim of a feedback control system is to keep the controlled variable close to its set point. It uses the difference between the controlled variable and its desired value to determine the input into the feedback controller. In the case of the self-balancing robot, the controlled variable will be the inclination angle and the set point will be the balance point. 

To maintains its balance, the robot will:
1. Determine the inclination angle from the MPU6050.
2. If it is tilted/falling, run the DC motors to compensate. For example, if the robot is falling forwards, the motors should go forward, shifting the robot to an upright position.
![Tilting diagram](http://127.0.0.1:4000/assets/PID_control/tilting_diagram.png)
3. This will continue in a closed loop. keeping the robot balanced.

How the motors will compensate for the tilting depends on the type of control system we choose to use.

### On-off Control
The on-off controller is the most basic type of control system. For the self-balancing robot, an on-off controller will work as follows.

1. If the robot is tilting forward, rotate the motors forwards.
2. If the robot is tilting backward, rotate the motors backwards.
3. If it is balanced, do nothing.

During this control loop, the motor will either be off or stay at a constant speed (which can be chosen arbitrarily). The on-off controller does not take the amount of tilt or speed at which the robot is falling into consideration, only the direction.

{: .highlight }
> Try to write your own on-off controller!


### Proportional Control
Another possible control system is proportional control. In proportional control, we take the difference between the current angle and desired angle into consideration when setting the speed of the motors. 

To apply proportional control to a self-balancing robot, the same logic as above is used, however, during each loop: 
1. The difference between the current and desired angle is calculated.
2. The difference, called the error term, is then multiplied by some constant $K_p$ to give an `output`.
3. This `output` then becomes the speed of the motor.

One thing to consider with this method is the maximum allowed input for the motor speed. PWM timers are 8-bit, therefore it only takes values from 0 to 255 (or 1111 1111). When using `analogWrite()` to modify the PWM and subsequent motor speed, we must limit the `output` to 255.

Using the proportional controller, it is possible to tune (by modifying the value of $K_p$) the robot so that it is mostly able to stay balance with little interference. However, this still does take how fast the robot is falling into account.

## PID Control
A more advance type of feedback control is PID control. 



PID control or Proportional-Integral-Derivative control not only takes the current error into consideration 


to do
- advantages
- explain each term in formula

### Integral
to do 

### Derivative 
to do 

### PID
to do - overall

- explain what increasing each variable does (wikipedia table)



## Arduino PID Library
In this project, we will be using a library to perform our PID calculations.

To install the PID library:
1. Click <a href="https://github.com/br3ttb/Arduino-PID-Library" and target="_blank">here</a> to access the library on GitHub.
2. Click on 'Code' and then 'Download ZIP' to download the .zip archive.
![Download library](http://127.0.0.1:4000/assets/PID_control/pid_library_1.png)
3. Locate your Arduino libraries folder on your device. There should be a folder called 'Arduino' under 'Documents'. Inside it will be a folder called 'Libraries'.
4. Unzip the archive's contents into your libraries folder.

### PID Calculation
To set up the PID feedback loop, we will be using the library function `pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT)`. `input` is the variable we are trying to control (i.e. the inclination angle), `setpoint` is our desired angle, `Kp`, `Ki` and `Kd` are our tuning variables, `output` is the resulting value of our PID calculations (to be set as the motor PWM input) and `DIRECT` is the direction that the output will move when faced with a given error.

```c++
// Before void setup()

/*********Tune these 4 values for your BOT*********/
double setpoint = 179.53;  //set the value when the bot is perpendicular to ground using serial monitor.
//Read the project documentation on circuitdigest.com to learn how to set these values
double Kp = 45;   //Set this first
double Kd = 2.1;  //Set this second 
double Ki = 320;  //Finally set this
/******End of values setting*********/

double input, output;

PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);
```

To initialise the the PID control, we must set the mode to automatic (as opposed to the default of off). We can also set the sample time to 10ms, compared to the default of 200ms, to improve its performance. Lastly, we can set the limits to -255 and 255.

```c++
//setup PID
pid.SetMode(AUTOMATIC);
pid.SetSampleTime(10); // calculates every 10ms
pid.SetOutputLimits(-255, 255);
```

To run the PID calculations, while there is no MPU data to process, we can use the function `pid.Compute()` which is called once every `loop()`. It will calculate a new output at the specified frequency, or do nothing in between. Once the PID calculation is complete we can use the new `output` to set the motor speed, and `input` to determine the motor direction.

{: .highlight }
> Complete your attempt at connecting the motor control and MPU6050 readings using a PID controller! If you get stuck, click <a href="https://lastminuteengineers.com/mpu6050-accel-gyro-arduino-tutorial/" target="_blank">here</a>.

<!-- change link once code is on github -->

## PID Tuning
The last step to completing your self-balancing robot is PID tuning. PID tuning is when you correctly set the PID variables (`Kp`, `Ki` and `Kd`) so that your controlled variable is able to stay as close as possible to its desired value. For the self-balancing robot, this desired value is the pitch angle when the robot is standing upright. You can determine this angle by reading the MPU while the robot is upright.

Manually tuning your self-balancing robot:
1. Set your `Kp` value to 1 and others to 0.
2. Steadily increase `Kp` until it is able to stay balanced with little interference. If your `Kp` value is too large, it will start to jitter uncontrollably.
3. Do the same with `Kd`.
4. Finish off by tuning `Ki`.
5. With the correct constants, your self-balancing robot should be able to maintain its balance even after being pushed softly.

{: .highlight }
> To see how a self-balancing robot was tuned, click <a href="https://www.youtube.com/watch?v=cjSw7sc2JKk&t=2s&ab_channel=CircuitDigest
" target="_blank">here</a>!

<!-- Embed the youtube video if possible -->

- explain what increasing each variable does (wikipedia table)


- attempt all 3 types of control cus y not :)\



https://playground.arduino.cc/Code/PIDLibrary/ 

documentation for pid library