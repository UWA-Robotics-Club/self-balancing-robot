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


{: .highlight }
> This page has been adapted from 'Last Minute Engineers'. For more info, visit their site 
 <a href="https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/
" target="_blank">here</a>!

### H-Bridge
We can control the direction of a DC motor by swapping the polarity of voltage applied to the motor. This is done through an electronic circuit called a H-bridge. A H-bridge consists of 4 switches which work together to control the polarity of voltage applied to the motor.

![H-Bridge circuit with all switches open](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/h_bridge/circuit.png)

![H-Bridge circuit with S1 and S4 closed](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/h_bridge/circuit (1).png)

![H-Bridge circuit with S2 and S3 closed](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/h_bridge/circuit (3).png)

As you can see from the above diagrams, closing switches S1 and S4 (with S2 and S3 open) causes the polarity of voltage applied to swap, compared to closing S2 and S3 (with S1 and S4 open). This will in turn cause the motor to rotate in the opposite direction.

If you close both switches on the same side (e.g. S1 and S2), a short circuit will occur. 

![H-bridge short circuit](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/h_bridge/circuit (2).png)

Additionally, if you close both switches on the top or bottom (e.g. S1 and S3), there will be no voltage drop through the motor causing it to be stationary.

![H-bridge circuit with S1 and S3 closed](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/h_bridge/circuit (4).png)

#### Summary

Here we will use '1' to represent a closed switch and '0' to represent an open switch.

| S1 | S2 | S3 | S4 | Result |
| :--- | :--- | :--- | :--- | :--- |
|  0  |  0  |  0  |  0  | Motor is stationary |
|  1  |  0  |  0  |  1  | Motor rotates clockwise |
|  0  |  1  |  1  |  0  | Motor rotates anti-clockwise |
|  0  |  1  |  0  |  1  | Motor is stationary |
|  1  |  0  |  1  |  0  | Motor is stationary |
|  1  |  1  |  0  |  0  | Short circuit |
|  0  |  0  |  1  |  1  | Short circuit |


### Pulse-Width Modulation (PWM)
Pulse-width modulation (PWM) is a way of varying the average power output of a digital signal by pulsing the digital signal on and off at different lengths of time. 

A PWM signal is a periodic rectangular signal which alternates between HIGH (5V on Arduinos) and LOW (0V). Decreasing the 'on'-time of the pulse results in a lower power output to the motor and hence a decrease in speed.

#### Definitions
T_on
: the amount of 'on'-time in a cycle.

T_off
: the amount of 'off'-time in a cycle.

Period (T)
: the total time in a cycle equal to the sum of the 'on' and 'off' time.

Duty cycle
: the percentage of 'on'-time in a period.
: $$ = \frac{T_{on}}{T} $$


![PWM signal](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pwm/pwm_labelled.png)

----

## Example

![PWM signals at different duty cycles](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pwm/Pulse-Width-Modulation.jpg)

For example, at a duty cycle of 25%, only 25% of the maximum (100% duty cycle) power output will be delivered to the motor. Therefore, if a duty cycle of 100% results in the motor spinning at 100 rpm, a 50% duty cycle will turn the motor at 50 rpm.

As a result, we can use PWM to control the speed of a DC motor.

----

### Pinout Diagram

![L298N Pinout](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/L298N-Motor-Driver-Module-Pinout.png)

The L298N motor driver module contains 3 power supply pins (VS, GND, VSS), 4 output (OUT) pins, 4 input (IN) pins and 2 enable (EN) pins.

adapted from: https://lastminuteengineers.com/l298n-dc-stepper-driver-arduino-tutorial/ 

#### Power Supply Pins

![L298N Power Supply Pinout](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/l298n_pinout_power.png)


| Pin  | Function | Connections |
| :--- | :---     | :---        |
| VCC |  Powers the motors connected to the module and accepts inputs from 5V to 12V  | Connected to the positive terminal of the power supply
| GND |  Common ground pin  | Connected to the negative terminal of the power supply |
| VSS or 5V |  Powers the logic circuit of the L298N module and accepts inputs of 5V to 7V  | Connected to positive terminal of another power supply |

![L298N Power Supply Connections](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/power_supply_l298N.png)


![L298N Regulators](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/l298n_pinout_regulator.png)


The L298N motor driver module also includes a regulator enable jumper which allows us to power the logic circuitry using the motor power supply. When the jumper is in place, we no longer need to connect a power supply to the VSS pin and can leave it open.

#### Output Motor Pins

![L298N Output Pins](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/l298n_pinout_output.png)

| Pin  | Function | Connections |
| :--- | :---     | :---        |
| OUT1 | Powers motor 1 | Connected to one side of motor 1 |
| OUT2 | Powers motor 1 | Connected to the other side of motor 1 |
| OUT3 | Powers motor 2 | Connected to one side of motor 2 |
| OUT4 | Powers motor 2 | Connected to the other side of motor 2 |

![L298N Motor Connections](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/output_l298N.png)


#### Direction Control Pins

![L298N Input Pins](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/l298n_pinout_input.png)

| Pin  | Function | Connections |
| :--- | :---     | :---        |
| IN1 | Controls the H-bridge switches (S... and S...) | Connected to a digital I/O pin |
| IN2 | Controls the H-bridge switches (S... and S...) | Connected to a digital I/O pin |
| IN3 | Controls the H-bridge switches (S... and S...) | Connected to a digital I/O pin |
| IN4 | Controls the H-bridge switches (S... and S...) | Connected to a digital I/O pin |

#### Speed Control Pins

![L298N Enable Pins](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/l298n_pinout_en.png)

| Pin  | Function | Connections |
| :--- | :---     | :---        |
| ENA | Control the power input to (and speed of) motor 1 | Connected to a digital I/O pin with PWM output  |
| ENB | Control the power input to (and speed of) motor 2 | Connected to a digital I/O pin with PWM output  |

On the Arduino Nano, digital I/O pins 3, 5, 6, 9, 10 and 11 are capable of PWM.

Make sure to disconnect the jumpers connecting 5V to ENA and ENB if you would like to use PWM to control the speed. The jumpers automatically set the enable pins to 5V (HIGH or 100% duty cycle).

Note: digital pins start with the letter 'D' (put this in footnote???)

![L298N Connections with Motors and Arduino Nano](https://uwa-robotics-club.github.io/self-balancing-robot/assets/motor_control/pinout/l298n_connections.png)

## Code Examples
Since the L298N is a dual H-bridge module, there are 2 separate H-bridges, allowing us to control each motor independently. In this code example, we will be controlling 'Motor 1' which is connected to OUT1 and OUT2. 

Before writing the motor control code, we must first initialise any digital I/O pins we will be using as output pins (as opposed to input pins). 

```c++
// Digital I/O pins connected to the motor driver
#define MOTOR1PIN1 10
#define MOTOR1PIN2 9
#define EN1 11

// Initialise the following pins as output 
pinMode(MOTOR1PIN1, OUTPUT);
pinMode(MOTOR1PIN2, OUTPUT);
pinMode(EN1, OUTPUT);
```

### Direction Control

As previously explained, opening and closing different switches of a H-bridge allows us to swap the direction of a motor. IN1 of the L298N controls switches S1 and S4. Applying 5V (HIGH) to IN1 closes S1 and S4, while connecting it to ground (0V) opens the switches. The same occurs with IN2 and switches S2 and S3. Therefore, to control the direction of the motor, we can set IN1 and IN2 to HIGH or LOW accordingly.

```c++
digitalWrite(MOTOR1PIN1, LOW); // Sets the output of MOTOR1PIN1 to 0V
digitalWrite(MOTOR1PIN2, HIGH); // Sets the output of MOTORPIN2 to 5V
```

### Speed Control
To control the speed of the motor, we can vary the duty cycle of our PWM output. In Arduino code, this is done using the function `analogWrite()`. This function takes 2 arguments, the I/O pin and an 8-bit value (0-255), with 0 being 0% duty cycle and 255 being 100% duty cycle.

```c++
analogWrite(EN1, 255); // Pick a number from 0 to 255 (255 being the fastest)
```

{: .highlight }
> For access to the full motor demo code click <a href="https://github.com/UWA-Robotics-Club/self-balancing-robot/blob/main/Motor_Control_Demo/Motor_Control_Demo.ino" target="_blank">here</a>.


