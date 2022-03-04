#include <Arduino.h>
#include <NewPing.h>

//Motor control pins
const int leftMotorVelocity = 10;
const int rightMotorVelocity = 9;

const int leftControl1 = 7;
const int leftControl2 = 6;

const int rightControl1 = 5;
const int rightControl2 = 4;

#define MAX_DISTANCE 50

NewPing sonarLeft(13, 12, MAX_DISTANCE);
NewPing sonarRight(3, 2, MAX_DISTANCE);
NewPing sonarFront(1, 0, MAX_DISTANCE);

void setup() 
{
  Serial.begin(9600); //Initialises serial connection 

  pinMode(leftMotorVelocity, OUTPUT);
  pinMode(rightMotorVelocity, OUTPUT);

  pinMode(leftControl1, OUTPUT);
  pinMode(leftControl2, OUTPUT);
  pinMode(rightControl1, OUTPUT);
  pinMode(rightControl2, OUTPUT);
  
  delay(3000);
}

void driveRight()
{

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(120);

  analogWrite(leftMotorVelocity, 255);
  analogWrite(rightMotorVelocity, 255);

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

void driveLeft()
{

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(120);

  analogWrite(leftMotorVelocity, 255);
  analogWrite(rightMotorVelocity, 255);

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

void reverse()
{
  analogWrite(leftMotorVelocity, 255);
  analogWrite(rightMotorVelocity, 255);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 0);
  delay(400);
}

void loop() 
{
  int right, left, front, divergence, speedRight, speedLeft;

  delay(50);
  front = sonarFront.ping_cm();

  delay(50);
  right = sonarRight.ping_cm();

  delay(50);
  left = sonarLeft.ping_cm();
  
  delay(50);

  divergence = (right - left);


  analogWrite(leftMotorVelocity, 255);
  analogWrite(rightMotorVelocity, 255);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  if (front > 21)
  {
    if (-1 <= divergence <= 1)
    {
      analogWrite(leftMotorVelocity, 255);
      analogWrite(rightMotorVelocity, 255);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }
    
    if (divergence > 1 && divergence <= 20)
    {
      speedRight = map(divergence, 1, 20, 255, 120);

      analogWrite(leftMotorVelocity, 255);
      analogWrite(rightMotorVelocity, speedRight);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }

    if (divergence < -1 && divergence >= -20)
    {
      speedLeft = map(abs(divergence), 1, 20, 255, 120);

      analogWrite(leftMotorVelocity, speedLeft);
      analogWrite(rightMotorVelocity, 255);

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

      analogWrite(leftMotorVelocity, 255);
      analogWrite(rightMotorVelocity, 255);

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

      analogWrite(leftMotorVelocity, 255);
      analogWrite(rightMotorVelocity, 255);

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

  if (right <= 3 && left <= 3 && front <= 3) reverse();

  if (left >= right && front <= 21) driveLeft();

  if (right > left && front <= 21) driveRight();
  
}

