#include <Arduino.h>
#include <NewPing.h>

//Motor control pins
const int leftMotorVelocity = 10;
const int rightMotorVelocity = 9;

const int leftControl1 = 7;
const int leftControl2 = 6;

const int rightControl1 = 5;
const int rightControl2 = 4;

const int rightStandard = 170;
const int leftStandard = 255;

#define MAX_DISTANCE 999

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

  Serial.begin(9600);

  delay(3000);
}

void driveRight()
{

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(120);

  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 255);
  analogWrite(rightControl2, 0);
  delay(150);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  delay(200);
}

void driveLeft()
{

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(120);

  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);
  delay(150);
  
  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  delay(200);
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
/*   Serial.println("front");
  Serial.println(front);
  delay(50); */

  right = sonarRight.ping_cm();
/*   Serial.println("right");
  Serial.println(right);
  delay(50); */

  left = sonarLeft.ping_cm();
/*   Serial.println("left");
  Serial.println(left);
  delay(50); */

  if (front == 0) {
    front = 999;
  }
  
  if (right == 0) {
    right = 999;
  }

  if (left == 0) {
    left = 999;
  }

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
      speedRight = map(divergence, 1, 15, 170, 0);
      speedRight = constrain(speedRight, 0, 170);

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
      speedLeft = map(divergence, 1, 15, 255, 0);
      speedLeft = constrain(speedLeft, 0, 255);

      analogWrite(leftMotorVelocity, speedLeft);
      analogWrite(rightMotorVelocity, rightStandard);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }

    if (divergence > 20)
    {

      analogWrite(leftMotorVelocity, 0);
      analogWrite(rightMotorVelocity, 0);

      delay(120);

      analogWrite(leftMotorVelocity, leftStandard);
      analogWrite(rightMotorVelocity, rightStandard);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 255);
      analogWrite(rightControl2, 0);
      delay(150);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);

      delay(250);
    }

    if (divergence < -20)
    {

      analogWrite(leftMotorVelocity, 0);
      analogWrite(rightMotorVelocity, 0);

      delay(120);

      analogWrite(leftMotorVelocity, leftStandard);
      analogWrite(rightMotorVelocity, rightStandard);

      analogWrite(leftControl1, 255);
      analogWrite(leftControl2, 0);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
      delay(150);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);

      delay(250);
    }
  }

  if ((right <= 3 && front <= 3) || (left <= 3 && front <= 3) || front <= 3) {
    unstuck();
    if (right <= left) driveLeft();
    else driveRight();
  }

  if (left >= right && front <= 21) driveLeft();

  if (right > left && front <= 21) driveRight();
  
}

