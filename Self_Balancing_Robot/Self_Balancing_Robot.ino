/* Arduino Self Balancing Robot
 * Adapted by: Dorothy Jong
 * From code by: B.Aswinth Raj
 * Build on top of Lib: https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
 * Website: circuitdigest.com 
 */

#include "I2Cdev.h"
#include <PID_v1.h>                      //From https://github.com/br3ttb/Arduino-PID-Library/blob/master/PID_v1.h
#include "MPU6050_6Axis_MotionApps20.h"  //https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050

MPU6050 mpu;

// Digital I/O pins connected to the motor driver
#define MOTOR1PIN1 10
#define MOTOR1PIN2 9
#define MOTOR2PIN1 8
#define MOTOR2PIN2 7
#define EN1 11
#define EN2 6

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


/*********Tune these 4 values for your BOT*********/
double setpoint = 179.53;  //set the value when the bot is perpendicular to ground using serial monitor.
double Kp = 45;            //Set this first
double Kd = 2.1;           //Set this second
double Ki = 320;           //Finally set this
/******End of values setting*********/

double input, output;

PID pid(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

volatile bool mpuInterrupt = false;  // indicates whether MPU interrupt pin has gone high

void dmpDataReady() {
  mpuInterrupt = true;
}

void setup() {

  Serial.begin(115200);

  // initialize device
  Serial.println(F("Initializing I2C devices..."));
  mpu.initialize();

  // verify connection
  Serial.println(F("Testing device connections..."));
  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

  // load and configure the DMP
  devStatus = mpu.dmpInitialize();

  // TO DO: SUPPLY YOUR OWN OFFSETS HERE! (From MPU_Calibration.ino)
  mpu.setXGyroOffset(1);
  mpu.setYGyroOffset(35);
  mpu.setZGyroOffset(-31);
  mpu.setZAccelOffset(1486);

  // make sure it worked (returns 0 if so)
  if (devStatus == 0) {
    // turn on the DMP, now that it's ready
    Serial.println(F("Enabling DMP..."));
    mpu.setDMPEnabled(true);

    // enable Arduino interrupt detection
    Serial.println(F("Enabling interrupt detection (Arduino external interrupt 0)..."));
    attachInterrupt(0, dmpDataReady, RISING);  // INT0 = D2
    mpuIntStatus = mpu.getIntStatus();
    // set our DMP Ready flag so the main loop() function knows it's okay to use it
    Serial.println(F("DMP ready! Waiting for first interrupt..."));
    dmpReady = true;

    // get expected DMP packet size for later comparison
    packetSize = mpu.dmpGetFIFOPacketSize();

    //setup PID
    pid.SetMode(AUTOMATIC);
    pid.SetSampleTime(10);
    pid.SetOutputLimits(-255, 255);
  }

  else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }


  //Initialise the Motor output pins
  pinMode(MOTOR1PIN1, OUTPUT);
  pinMode(MOTOR1PIN2, OUTPUT);
  pinMode(MOTOR2PIN1, OUTPUT);
  pinMode(MOTOR2PIN2, OUTPUT);

  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  //By default turn off both the motors
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, LOW);

  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
}



void loop() {
  // if programming failed, don't try to do anything
  if (!dmpReady) return;
  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {
    //no mpu data - performing PID calculations and output to motors
    pid.Compute();

    //Print the value of Input and Output on serial monitor to check how it is working.
    Serial.print(input);
    Serial.print(" =>");
    Serial.println(output);

    // Modify range to +- 30 degrees from 180
    if (input > 150 && input < 210) {  //If the Bot is falling
      if (output > 0)                  //Falling towards front
      {
        forward();            //Rotate the wheels forward
      } else if (output < 0)  //Falling towards back
      {
        reverse();  //Rotate the wheels backward
      }
    } else  //If Bot not falling
    {
      stop();  //Hold the wheels still
    }
  }

  // reset interrupt flag and get INT_STATUS byte
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();

  // get current FIFO count
  fifoCount = mpu.getFIFOCount();

  // check for overflow (this should never happen unless our code is too inefficient)
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    // reset so we can continue cleanly
    mpu.resetFIFO();
    Serial.println(F("FIFO overflow!"));
    // otherwise, check for DMP data ready interrupt (this should happen frequently)
  } else if (mpuIntStatus & 0x02) {
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
  }
}

void forward()  //Code to rotate the wheel forward
{
  digitalWrite(MOTOR1PIN1, LOW);   // Sets the output of MOTOR1PIN1 to 0V
  digitalWrite(MOTOR1PIN2, HIGH);  // Sets the output of MOTORPIN2 to 5V
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);

  Serial.println("F");  // For debugging
}

void reverse()  //Code to rotate the wheel reverse
{
  digitalWrite(MOTOR1PIN1, HIGH);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, HIGH);
  digitalWrite(MOTOR2PIN2, LOW);

  Serial.println("R");  // For debugging
}

void stop()  //Code to stop both the wheels
{
  digitalWrite(MOTOR1PIN1, LOW);
  digitalWrite(MOTOR1PIN2, LOW);
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, LOW);

  Serial.println("S");  // For debugging
}
