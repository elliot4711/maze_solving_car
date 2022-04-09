#include <Arduino.h>
#include <NewPing.h>

//Motor control pins
const int leftMotorVelocity = 9;
const int rightMotorVelocity = 10;

const int leftControl1 = 4;
const int leftControl2 = 5;

const int rightControl1 = 6;
const int rightControl2 = 7;

const int rightStandard = 252 * 0.785;
const int leftStandard = 255 * 0.785;
const int rightMax = 252;
const int leftMax = 255;

#define MAX_DISTANCE 50
#define STOP_DISTANCE 21

NewPing sonarLeft(13, 12, MAX_DISTANCE);
NewPing sonarRight(3, 2, MAX_DISTANCE);
NewPing sonarFront(11, 8, MAX_DISTANCE);

float Kp = 3; //set up the constants value
float Ki = 0;
float Kd = 4.4;
int P;
int I;
int D;

int lastError = 0;

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

// void loop() {
//   analogWrite(leftMotorVelocity, leftMax);
//   analogWrite(rightMotorVelocity, rightMax);

//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 255);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 255);
// }

void loop() {
  int right, left, front, speedRight, speedLeft, error, motorspeed;
  
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

  Serial.println("front");
  Serial.println(front);
  Serial.println("right");
  Serial.println(right);
  Serial.println("left");
  Serial.println(left);

  if (left > 35){
    int startTime = millis();
    int time = millis();
    int duration = time - startTime;
    while (duration < 400){
      left = sonarLeft.ping_cm();
      if (left == 0) {
        left = MAX_DISTANCE;
      }
      error = 8 - left;
      P = error;
      I = I + error;
      D = error - lastError;
      lastError = error;
      motorspeed = P*2.5 + I*0 + D*0;

      speedRight = rightStandard - (motorspeed * 0.99);
      speedLeft = leftStandard + motorspeed;
      if (speedRight > rightMax)
      {
        speedRight = rightMax;
      }
      if (speedLeft > leftMax)
      {
        speedLeft = leftMax;
      }
      if (speedRight < 0)
      {
        speedRight = 0;
      }
      if (speedLeft < 0)
      {
        speedLeft = 0;
      }

      analogWrite(leftMotorVelocity, speedLeft);
      analogWrite(rightMotorVelocity, speedRight);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
      
      time = millis();
      duration = time - startTime;
    }
    analogWrite(leftMotorVelocity, leftStandard);
    analogWrite(rightMotorVelocity, rightStandard);
    delay(150);
  }

  if (right > 35){
    int startTime = millis();
    int time = millis();
    int duration = time - startTime;
    while (duration < 400){
      right = sonarRight.ping_cm();
      if (right == 0) {
        right = MAX_DISTANCE;
      }
      error = right - 8;
      P = error;
      I = I + error;
      D = error - lastError;
      lastError = error;
      motorspeed = P*2.5 + I*0 + D*0;

      speedRight = rightStandard - (motorspeed * 0.99);
      speedLeft = leftStandard + motorspeed;
      if (speedRight > rightMax)
      {
        speedRight = rightMax;
      }
      if (speedLeft > leftMax)
      {
        speedLeft = leftMax;
      }
      if (speedRight < 0)
      {
        speedRight = 0;
      }
      if (speedLeft < 0)
      {
        speedLeft = 0;
      }

      analogWrite(leftMotorVelocity, speedLeft);
      analogWrite(rightMotorVelocity, speedRight);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
      
      time = millis();
      duration = time - startTime;
      delay(25);
    }
    analogWrite(leftMotorVelocity, leftStandard);
    analogWrite(rightMotorVelocity, rightStandard);
    delay(150);
  }

  else{
    error = right - left;

    P = error;
    I = I + error;
    D = error - lastError;
    lastError = error;
    motorspeed = P*Kp + I*Ki + D*Kd;
  
    speedRight = rightStandard - (motorspeed * 0.99);
    speedLeft = leftStandard + motorspeed;
    if (speedRight > rightMax)
    {
      speedRight = rightMax;
    }
    if (speedLeft > leftMax)
    {
      speedLeft = leftMax;
    }
    if (speedRight < 0)
    {
      speedRight = 0;
    }
    if (speedLeft < 0)
    {
      speedLeft = 0;
    }

    analogWrite(leftMotorVelocity, speedLeft);
    analogWrite(rightMotorVelocity, speedRight);

    analogWrite(leftControl1, 0);
    analogWrite(leftControl2, 255);
    analogWrite(rightControl1, 0);
    analogWrite(rightControl2, 255);
    
    delay(25);
  }
}
