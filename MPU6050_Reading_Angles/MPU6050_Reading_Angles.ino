/* Reading the Inclination Angle from an MPU6050
 * Adapted by: Dorothy Jong
 * From code by: B.Aswinth Raj (circuitdigest.com)
 * Build on top of Lib: https://github.com/jrowberg/i2cdevlib/tree/master/Arduino/MPU6050
 */


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
  mpu.setXGyroOffset(-1);
  mpu.setYGyroOffset(35);
  mpu.setZGyroOffset(-31);
  mpu.setZAccelOffset(1496);

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
  else {
    // ERROR!
    // 1 = initial memory load failed
    // 2 = DMP configuration updates failed
    // (if it's going to break, usually the code will be 1)
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}


void loop() {
  // if programming failed, don't try to do anything
  if (!dmpReady) return;
  // wait for MPU interrupt or extra packet(s) available
  while (!mpuInterrupt && fifoCount < packetSize) {
    //no mpu data
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

    Serial.println(input);
  }
}

