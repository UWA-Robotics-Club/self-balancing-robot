---
layout: default
title: Motor Control
nav_order: 3
#parent: ..
#has_children: ...
---

# Motor Control
{: .no_toc }

<details open markdown="block">
  <summary>
    Table of contents
  </summary>
  {: .text-delta }
1. TOC
{:toc}
</details>

## The L298N Motor Driver Module
To control the speed and direction of the 2 DC motors, we will be using the L298N motor driver. The L298N contains 2 H-bridges which allows us to control the direction of 2 DC motors individually, while pulse-width modulation (PWM) will be used to control the speed of the motors.

### H-Bridge
We can control the direction of a DC motor by swapping the polarity of voltage applied to the motor. This is done through an electronic circuit called a H-bridge. A H-bridge consists of 4 switches which work together to control the polarity of voltage applied to the motor.

- This is the picture of h-bridge with all switches open
![alt text](http://127.0.0.1:4000/assets/circuit.png)

- This is the picture with S1 and S4 closed
![alt text](http://127.0.0.1:4000/assets/circuit (1).png)
- This is the picture with S2 and S3 closed
![alt text](http://127.0.0.1:4000/assets/circuit (3).png)

As you can see from the above diagrams, closing switches S1 and S4 (with S2 and S3 open) causes the polarity of voltage applied to swap, compared to closing S2 and S3 (with S1 and S4 open). This will in turn cause the motor to rotate in the opposite direction.

- add gif from website if possible

If you close both switches on the same side (e.g. S1 and S2), a short circuit will occur. 

![alt text](http://127.0.0.1:4000/assets/circuit (2).png)

Additionally, if you close both switches on the top or bottom (e.g. S1 and S3), there will be no voltage drop through the motor causing it to be stationary.

![alt text](http://127.0.0.1:4000/assets/circuit (4).png)

ADD TRUTH TABLE??

Summary??

Here we will use '1' to represent a closed switch and '0' to represent an open switch.

| S1 | S2 | S3 | S4 | Result |
| :--- | :--- | :--- | :--- | :--- |
|  0  |  0  |  0  |  0  | Motor is stationary |
|  1  |  0  |  0  |  1  | Motor rotates clockwise? |
|  0  |  1  |  1  |  0  | Motor rotates anti-clockwise? |
|  0  |  1  |  0  |  1  | Motor is stationary |
|  1  |  0  |  1  |  0  | Motor is stationary |
|  1  |  1  |  0  |  0  | Short circuit |
|  0  |  0  |  1  |  1  | Short circuit |


DONE


... takes 2 binary (HIGH or LOW) inputs to …

### Pulse-Width Modulation (PWM)
Pulse-width modulation (PWM) is a way of varying the average power output of a digital signal by pulsing the digital signal on and off at different lengths of time. 

A PWM signal is a periodic signal ....

- talk about its periodicity


Decreasing the 'on'-time of the pulse results in a lower power output to the motor and hence a decrease in speed.

#### Definitions
T_on
: the amount of 'on'-time in a cycle.

T_off
: the amount of 'off'-time in a cycle.

Period (T)
: the total time in a cycle equal to the sum of the 'on' and 'off' time.

Duty cycle
: the percentage of 'on'-time in a period.
: $$ \frac{T_{on}}{T} $$
: = T_on/T





In an Arduino board, the digital pins output a voltage of 5V when set to HIGH and 0V when set to LOW. Therefore, a duty cycle of 50% will result in a 

### Pinout Diagram
TO DO

## Code Examples
TO DO