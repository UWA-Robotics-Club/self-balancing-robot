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
In this project, we will be using the MPU6050 to measure the robot's orientation and movement in real time. The MPU6050 is a small, low-cost sensor module that contains both an accelerometer and a gyroscope. The accelerometer in the MPU6050 measures acceleration in 3 dimensions (x, y and z), while the gyroscope measure angular velocity around those same dimensions. 

![3 axes on MPU6050](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/mpu_ypr.png)

### MPU6050 Pinout 
In this self-balancing robot, we will only be using the VCC, GND, SCL, SDA, and INT pins.

![MPU6050 pinout diagram](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/mpu6050_pinout.png)

| Pin  | Function | Connections |
| :--- | :---     | :---        |
| VCC | To supply power to the module | Connected to 5V or 3V3 pins on the Arduino Nano |
| GND | Common ground pin | Connected to GND on the Arduino Nano |
| SCL | Serial clock pin - provides the clock pulse for I2C Communication | Connected to A5 on the Arduino Nano |
| SDA | Serial data pin - to transfer data through I2C communication | Connected to A4 on the Arduino Nano |
| INT | Interrupt output pin - to indicate that data is available for the Arduino Nano to read. | Connect to D2 on the Arduino Nano |

<!-- https://components101.com/sensors/mpu6050-module -->

![MPU6050 connections](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/mpu6050_connections.png)

{: .highlight }
> The MPU6050 module contains a 3.3V regulator which allows us to connect it to either the 5V or 3V3 pins on the Arduino Nano.
![MPU6050 power regulator](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/mpu6050_regulator.png)

## MPU6050 Software
For the self-balancing robot, we will need to measure the angle of inclination (or 'tilt' angle) in real time. This allows the microcontroller to determine whether or not the robot is leaning to one side and adjust accordingly.

### Libraries
There are many Arduino libraries available which allows us to measure the orientation of the MPU6050, however, we will be using the <a href="https://github.com/jrowberg/i2cdevlib" target="_blank">I2C Device Library</a>. 

To install the I2C Device Library:
1. Navigate to the I2C Device Library Github repository by clicking <a href="https://github.com/jrowberg/i2cdevlib" target="_blank">here</a>.
2. Download a .zip archive of the repository by clicking 'Code' followed by 'Download ZIP'.
![MPU6050 connections](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/I2C_1.png)
3. Locate your Arduino libraries folder on your device. There should be a folder called 'Arduino' under 'Documents'. Inside it will be a folder called 'Libraries'.
4.  Find the 'Arduino/I2Cdev' and 'Arduino/MPU6050' folders in the .zip archive and copy it into your libraries folder for Arduino.

{: .highlight }
> For more information on I2C communication, click <a href="https://www.circuitbasics.com/basics-of-the-i2c-communication-protocol/" target="_blank">here</a>!.

### Calibrating the MPU6050
To calibrate the MPU6050, we will be applying a level of abstraction and running the Arduino code found <a href="https://github.com/UWA-Robotics-Club/self-balancing-robot/blob/main/MPU6050_Calibration/MPU6050_Calibration.ino" target="_blank">here</a>.

1. Download the above Arduino code onto your device.
2. Upload the code onto the Arduino Nano.
3. Open 'Serial Monitor'. Make sure that your Baud rate is at 115200.
4. Follow the instructions listed in the Serial Monitor. This may take a while.
![Start calibrating](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/mpu6050_calibration_1.png)
![Calibrating](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/mpu6050_calibration_2.png)
5. Note down the offset values for `acelZ`, `gyroX`, `gyroY` and `gyroZ`.
![Offsets from calibration](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/mpu_calibration_3.png)
<!-- Fix above image to have correct spelling -->

These offset values calibrate the MPU6050's digital motion processor (DMP) which combines data from the accelerometer and gyroscope into angles that we can read.

{: .highlight }
> An easy way to verify that the libraries have been installed correctly is to verify the code before uploading.


### Reading the Inclination Angle
In order to determine the inclination angle of our self-balancing robot, we will be writing some Arduino code to interface between the Arduino Nano and MPU6050.

#### Setup()

The first step when writing code is to initialise all of the required libraries and variables.

```c++
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"  //https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050

MPU6050 mpu;

// MPU control/status vars

bool dmpReady = false;   // set true if DMP (digital motion processor) init was successful
uint8_t mpuIntStatus;    // holds actual interrupt status byte from MPU 
uint8_t devStatus;       // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;     // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;      // count of all bytes currently in FIFO
uint8_t fifoBuffer[64];  // FIFO storage buffer

// orientation/motion vars

Quaternion q;         // [w, x, y, z]         quaternion container
VectorFloat gravity;  // [x, y, z]            gravity vector
float ypr[3];         // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

double input;

volatile bool mpuInterrupt = false;  // indicates whether MPU interrupt pin has gone high
```

The next step is to initialise the MPU6050 and verify its connection in `setup()`. We must also load and configure the MPU6050's digital motion processor seperately. For easy debugging, we have `Serial.println()` statements which are displayed in the Serial Monitor while the code is running.

```c++
  Serial.begin(115200);

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // load and configure the DMP
  devStatus = mpu.dmpInitialize();
```

After initialisation, we set the offsets which were determined during calibration into our code to make the MPU readings more accurate.

```c++
   // TO DO: SUPPLY YOUR OWN OFFSETS HERE! (From MPU_Calibration.ino)
  mpu.setXGyroOffset(-1);
  mpu.setYGyroOffset(35);
  mpu.setZGyroOffset(-31);
  mpu.setZAccelOffset(1496);
```

For additional error checking, we will check that the DMP was initialised successfully. 
If so, we can turn it on. Lastly, we must set up the interrupt detection system so that the microcontroller will be notified when data from the MPU6050 is ready to be processed. To do this, we can use the function `attachInterrupt(pin, ISR, mode)`. In the below code snippet, `0` refers to the interrupt pin number (INT0 corresponding to D2), while `dmpDataReady` is a helper function which sets the interrupt flag to `TRUE`. `RISING` means that an interrupt will be triggered when the pin goes from low to high.

```c++
// make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(0, dmpDataReady, RISING); // INT0 = D2

    mpuIntStatus = mpu.getIntStatus();
    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();
  }
```

#### Loop()
Firstly, we will wait for an interrupt from the MPU to signal that a data packet is available (or if extra data packets are in the queue). 

```c++
// if programming failed, don't try to do anything
  if (!dmpReady) return;
  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {
    //no mpu data
  }
```

Once data has been received, we must reset the interrupt flag. We then get the interrupt status of the MPU and update the size of the FIFO (first-in-first-out) data buffer.

```c++
// reset interrupt flag and get INT_STATUS byte
mpuInterrupt = false;
mpuIntStatus = mpu.getIntStatus();
// get current FIFO count
fifoCount = mpu.getFIFOCount();
```

Through this updated buffer size, we can check for overflow. 
```c++
// check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));
  }
```

Next, we can check that the DMP data is ready using the interrupt status. If it is not ready, the loop will restart. When there is data available with the correct size, we will read the data packet and update the FIFO count.

Lastly, to obtain the yaw, pitch and roll, we need to get the quarternion and gravity value first. Then use the library function `mpu.dmpGetYawPitchRoll()` to read the values into the `ypr[]` array. The inclination angle will then be the pitch (rotation along the y-axis), which is `ypr[1]`. This value is converted from radians to degrees and is stored in the variable `input`.

```c++
// otherwise, check for DMP data ready interrupt (this should happen frequently)
else if (mpuIntStatus & 0x02) {
    // wait for correct available data length, should be a VERY short wait
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    // read a packet from FIFO
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    // track FIFO count here in case there is > 1 packet available
    // (this lets us immediately read more without waiting for an interrupt)
    fifoCount -= packetSize;
    mpu.dmpGetQuaternion(&q, fifoBuffer);       //get value for q
    mpu.dmpGetGravity(&gravity, &q);            //get value for gravity
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);  //get value for ypr
    input = ypr[1] * 180 / M_PI + 180;          // Input is pitch in degrees

    Serial.println(input);
  }
```

When the self-balancing robot is upright (i.e. the MPU6050 module is laying flat with X, Y and Z symbols visible), the `input` value should be equal to approximately 180.

![Reading angles](https://uwa-robotics-club.github.io/self-balancing-robot/assets/accelerometer_and_gyroscope/reading_angles.png)

{: .highlight }
> Access to the full MPU6050 demo code can be found <a href="https://github.com/UWA-Robotics-Club/self-balancing-robot/blob/main/MPU6050_Reading_Angles/MPU6050_Reading_Angles.ino" and target="_blank">here</a> and to read more about the MPU6050 click <a href="https://lastminuteengineers.com/mpu6050-accel-gyro-arduino-tutorial/" target="_blank">here</a>!


<!-- https://mjwhite8119.github.io/Robots/mpu6050#:~:text=The%20next%20step%20is%20to,firmware%20in%20order%20to%20run. -->