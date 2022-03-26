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

#define MAX_DISTANCE 30

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

void driveRight()
{

  delay(200);

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(120);

  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 255);
  analogWrite(rightControl2, 0);

  delay(100);
  
  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 0);

  delay(120);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  delay(500);
}

void driveLeft()
{

  delay(200);

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(120);

  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);
  delay(100);
  
  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 0);

  delay(120);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  delay(500);
}

void unstuck()
{
  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 255);
  analogWrite(rightControl2, 0);
  delay(400);
}

void loop() 
{
  int right, left, front, divergence, speedRight, speedLeft;

  front = sonarFront.ping_cm();

  right = sonarRight.ping_cm();

  left = sonarLeft.ping_cm();

  if (front == 0) {
    front = 30;
  }
  
  if (right == 0) {
    right = 30;
  }

  if (left == 0) {
    left = 30;
  }

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

  if (front > 21)
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
    
    if (divergence > 1 && divergence <= 20)
    {
      speedRight = map(divergence, 1, 15, rightStandard, 0);
      speedRight = constrain(speedRight, 0, rightStandard);

      analogWrite(leftMotorVelocity, leftStandard);
      analogWrite(rightMotorVelocity, speedRight);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }

    if (divergence < -1 && divergence >= -20)
    {
      divergence = abs(divergence);
      speedLeft = map(divergence, 1, 15, leftStandard, 0);
      speedLeft = constrain(speedLeft, 0, leftStandard);

      analogWrite(leftMotorVelocity, speedLeft);
      analogWrite(rightMotorVelocity, rightStandard);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }

    if (right >= 30)
    {
      driveRight();
    }

    if (left > 30)
    {
      driveLeft();
    }
  }

  if ((right <= 2) || (left <= 2) || front <= 4) {
    unstuck();
    if (right <= left) driveLeft();
    else driveRight();
  }

  if (left >= right && front <= 21) driveLeft();

  if (right > left && front <= 21) driveRight();
  
}

