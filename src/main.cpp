#include <Arduino.h>
#include <NewPing.h>

//Motor control pins
const int leftMotorVelocity = 9;
const int rightMotorVelocity = 10;

const int leftControl1 = 4;
const int leftControl2 = 5;

const int rightControl1 = 6;
const int rightControl2 = 7;

const int rightStandard = 255;
const int leftStandard = 255;

#define MAX_DISTANCE 50
#define STOP_DISTANCE 21

NewPing sonarLeft(13, 12, MAX_DISTANCE);
NewPing sonarRight(3, 2, MAX_DISTANCE);
NewPing sonarFront(11, 8, MAX_DISTANCE);

void setup() 
{
  pinMode(leftMotorVelocity, OUTPUT);
  pinMode(rightMotorVelocity, OUTPUT);

  pinMode(leftControl1, OUTPUT);
  pinMode(leftControl2, OUTPUT);
  pinMode(rightControl1, OUTPUT);
  pinMode(rightControl2, OUTPUT);
  
  // Serial.begin(9600);

  delay(3000);
}

// void loop() {
//   analogWrite(leftMotorVelocity, leftStandard);
//   analogWrite(rightMotorVelocity, rightStandard);

//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 255);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 255);
// }

void driveRight()
{
  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(250);

  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 255);
  analogWrite(rightControl2, 0);

  delay(210);
  
  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 0);

  delay(200);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  int front;
  unsigned long then, duration;

  front = sonarFront.ping_cm();
  if (front == 0) {
    front = MAX_DISTANCE;
  }
  then = millis();
  while (front >= STOP_DISTANCE){
    front = sonarFront.ping_cm();
    if (front == 0) {
    front = MAX_DISTANCE;
    }
    duration = millis() - then;
    if (duration > 600) {
      break;
    }

  }

}

void driveLeft()
{
  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(250);

  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);
  delay(210);
  
  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 0);

  delay(200);
  
  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);
  
  int front;
  unsigned long then, duration;

  front = sonarFront.ping_cm();
  if (front == 0) {
    front = MAX_DISTANCE;
  }
  then = millis();
  while (front >= STOP_DISTANCE){
    front = sonarFront.ping_cm();
    if (front == 0) {
    front = MAX_DISTANCE;
    }
    duration = millis() - then;
    if (duration > 600) {
      break;
    }

  }

}

void unstuck()
{
  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 255);
  analogWrite(rightControl2, 0);
  delay(500);
}

void loop() 
{
  int right, left, front, divergence, speedRight, speedLeft;

  front = sonarFront.ping_cm();

  right = sonarRight.ping_cm();

  left = sonarLeft.ping_cm();

  if (front == 0) {
    front = MAX_DISTANCE;
  }
  
  if (right == 0) {
    right = MAX_DISTANCE;
  }

  if (left == 0) {
    left = MAX_DISTANCE;
  }
  delay(50);

/*   Serial.println("front");
  Serial.println(front);
  delay(50);
  
  Serial.println("right");
  Serial.println(right);
  delay(50);

  Serial.println("left");
  Serial.println(left);
  delay(50); */

  divergence = (right - left);

  if (front > STOP_DISTANCE)
  {
    if (-1 >= divergence && divergence <= 1)
    {
      analogWrite(leftMotorVelocity, leftStandard);
      analogWrite(rightMotorVelocity, rightStandard);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }
    
    if (divergence >1 && divergence <= 30)
    {
      speedRight = map(divergence, 1, 5, rightStandard, 235);
      speedRight = constrain(speedRight, 235, rightStandard);

      analogWrite(leftMotorVelocity, leftStandard);
      analogWrite(rightMotorVelocity, speedRight);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }

    if (divergence < -1 && divergence >= -30)
    {
      divergence = abs(divergence);
      speedLeft = map(divergence, 1, 5, leftStandard, 235);
      speedLeft = constrain(speedLeft, 235, leftStandard);

      analogWrite(leftMotorVelocity, speedLeft);
      analogWrite(rightMotorVelocity, rightStandard);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);

    }

    if (right > 40)
    {
      driveRight();
    }

    if (left >= 40)
    {
      driveLeft();
    }
  }

  if ((right <= 2) || (left <= 2) || front <= 4) {
    unstuck();
    if (right <= left) {
      analogWrite(leftMotorVelocity, leftStandard);
      analogWrite(rightMotorVelocity, rightStandard);

      analogWrite(leftControl1, 255);
      analogWrite(leftControl2, 0);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
      delay(100);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
      delay(100);
    }
    else {
      analogWrite(leftMotorVelocity, leftStandard);
      analogWrite(rightMotorVelocity, rightStandard);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 255);
      analogWrite(rightControl2, 0);
      delay(100);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
      delay(100);
    }
  }

  if (left >= right && front <= STOP_DISTANCE) driveLeft();

  if (right > left && front <= STOP_DISTANCE) driveRight();
  
}

