/*
* URC Self-Balancing Robot - Motor Control Demo
* 
* Author: Dorothy Jong
*/


// Digital I/O pins connected to the motor driver
#define MOTOR1PIN1 10
#define MOTOR1PIN2 9
#define MOTOR2PIN1 8
#define MOTOR2PIN2 7
#define EN1 11
#define EN2 6

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Initialise the following pins as output 
  pinMode(MOTOR1PIN1, OUTPUT);
  pinMode(MOTOR1PIN2, OUTPUT);
  pinMode(MOTOR2PIN1, OUTPUT);
  pinMode(MOTOR2PIN2, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);

  // Speed Control
  analogWrite(EN1, 255); // Pick a number from 0 to 255 (255 being the fastest)
  analogWrite(EN2, 255); 

}

void loop() {
  // put your main code here, to run repeatedly:

  forward(); // Calls helper functions below
  delay(5000); // Delays the program for 5000 ms or 5 secs

  stop();
  delay(5000);

  reverse();
  delay(5000);

  stop();
  delay(5000);

}

void forward()  //Code to rotate the wheel forward
{
  digitalWrite(MOTOR1PIN1, LOW); // Sets the output of MOTOR1PIN1 to 0V
  digitalWrite(MOTOR1PIN2, HIGH); // Sets the output of MOTORPIN2 to 5V
  digitalWrite(MOTOR2PIN1, LOW);
  digitalWrite(MOTOR2PIN2, HIGH);

  Serial.println("F"); // For debugging
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

  Serial.println("S"); // For debugging
}
