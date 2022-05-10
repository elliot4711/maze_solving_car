#include <Arduino.h>
#include <NewPing.h>

//Motor control pins
const int leftMotorVelocity = 9;
const int rightMotorVelocity = 10;

const int leftControl1 = 4;
const int leftControl2 = 5;

const int rightControl1 = 6;
const int rightControl2 = 7;

const int rightStandard = 255 * 0.85;
const int leftStandard = 255 * 0.85; //0.785
const int rightMax = 255;
const int leftMax = 255;
const int rightMin = 140;
const int leftMin = 125;

#define MAX_DISTANCE 50

NewPing sonarLeft(13, 12, MAX_DISTANCE);
NewPing sonarRight(3, 2, MAX_DISTANCE);
NewPing sonarFront(11, 8, MAX_DISTANCE);

float Kp = 0.0195; //set up the constants value 1.5
float Ki = 0.0003; //maybe 0.001
float Kd = 0.65; //2.5 /0.4
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

  delay(3000);
}

// void loop() {
//   analogWrite(leftMotorVelocity, 242);
//   analogWrite(rightMotorVelocity, 255);

//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 255);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 255);
// }

void loop() {
  int right, left, front, speedRight, speedLeft, error, correction, leftError, rightError;
  
  front = sonarFront.ping();

  right = sonarRight.ping();

  left = sonarLeft.ping();

  if (front == 0) {
    front = 2940;
  }
  
  if (right == 0) {
    right = 2940;
  }

  if (left == 0) {
    left = 2940;
  }

  if (right > 2059){
    int startTime = millis();
    int time = millis();
    int duration = time - startTime;
    
    rightError = (right - 588)*2;
      
    P = rightError;

    correction = P*Kp;

    speedRight = rightStandard - (correction);
    speedLeft = leftStandard + (correction);
    
    if (speedRight > rightMax)
    {
      speedRight = rightMax;
    }
    if (speedLeft > leftMax)
    {
      speedLeft = leftMax;
    }
    if (speedRight < rightMin)
    {
      speedRight = rightMin;
    }
    if (speedLeft < leftMin)
    {
      speedLeft = leftMin;
    }

    analogWrite(leftMotorVelocity, speedLeft);
    analogWrite(rightMotorVelocity, speedRight);

    analogWrite(leftControl1, 0);
    analogWrite(leftControl2, 255);
    analogWrite(rightControl1, 0);
    analogWrite(rightControl2, 255);
    
    while (right > 706){
      right = sonarRight.ping();
      if (right == 0) {
        right = 2940;
      }
      front = sonarFront.ping();
      if (front == 0) {
        front = 2940;
      }
      rightError = (right - 588)*2;
      
      P = rightError;

      correction = P*Kp;

      speedRight = rightStandard - (correction);
      speedLeft = leftStandard + (correction);
      
      if (speedRight > rightMax)
      {
        speedRight = rightMax;
      }
      if (speedLeft > leftMax)
      {
        speedLeft = leftMax;
      }
      if (speedRight < rightMin)
      {
        speedRight = rightMin;
      }
      if (speedLeft < leftMin)
      {
        speedLeft = leftMin;
      }

      analogWrite(leftMotorVelocity, speedLeft);
      analogWrite(rightMotorVelocity, speedRight);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
      
      time = millis();
      duration = time - startTime;
      if (duration > 1000){
        break;
      }

      if ((front < 1647) && (right < 824)) {
        break;
      }

      if (front < 941) {
        break;
      }
      delay(30);
    }
  }

  else if (left > 2059){
    int startTime = millis();
    int time = millis();
    int duration = time - startTime;

    leftError = (588 - left)*2;
    
    P = leftError;
    
    correction = P*Kp;

    speedRight = rightStandard - (correction);
    speedLeft = leftStandard + (correction);
    
    if (speedRight > rightMax)
    {
      speedRight = rightMax;
    }
    if (speedLeft > leftMax)
    {
      speedLeft = leftMax;
    }
    if (speedRight < rightMin)
    {
      speedRight = rightMin;
    }
    if (speedLeft < leftMin)
    {
      speedLeft = leftMin;
    }

    analogWrite(leftMotorVelocity, speedLeft);
    analogWrite(rightMotorVelocity, speedRight);

    analogWrite(leftControl1, 0);
    analogWrite(leftControl2, 255);
    analogWrite(rightControl1, 0);
    analogWrite(rightControl2, 255);
    
    while (left > 706){
      left = sonarLeft.ping();
      if (left == 0) {
        left = 2940;
      }
      front = sonarFront.ping();
      if (front == 0) {
        front = 2940;
      }
      
      leftError = (588 - left)*2;
      P = leftError;
      
      correction = P*Kp;

      speedRight = rightStandard - (correction);
      speedLeft = leftStandard + (correction);
      
      if (speedRight > rightMax)
      {
        speedRight = rightMax;
      }
      if (speedLeft > leftMax)
      {
        speedLeft = leftMax;
      }
      if (speedRight < rightMin)
      {
        speedRight = rightMin;
      }
      if (speedLeft < leftMin)
      {
        speedLeft = leftMin;
      }

      analogWrite(leftMotorVelocity, speedLeft);
      analogWrite(rightMotorVelocity, speedRight);

      analogWrite(leftControl1, 0);
      analogWrite(leftControl2, 255);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
      
      time = millis();
      duration = time - startTime;
      if (duration > 1000){
        break;
      }

      if ((front < 1647) && (left < 824)) {
        break;
      }

      if (front < 941) {
        break;
      }
      delay(30);
    }
  }

  else{
    error = right - left;

    P = error;
    I = I + error;
    D = error - lastError;
    lastError = error;
    
    correction = P*Kp + I*Ki + D*Kd;

    long startTime = millis();
    if (abs(D) <= 30 && startTime > 8000){
      int standard = map(abs(D), 0, 30, 255, rightStandard);
      speedRight = standard - (correction);
      speedLeft = standard + (correction);
    }
    else {
      speedRight = rightStandard - (correction);
      speedLeft = leftStandard + (correction);
    }
    
    if (speedRight > rightMax)
    {
      speedRight = rightMax;
    }
    if (speedLeft > leftMax)
    {
      speedLeft = leftMax;
    }
    if (speedRight < rightMin)
    {
      speedRight = rightMin;
    }
    if (speedLeft < leftMin)
    {
      speedLeft = rightMin;
    }

    analogWrite(leftMotorVelocity, speedLeft);
    analogWrite(rightMotorVelocity, speedRight);

    analogWrite(leftControl1, 0);
    analogWrite(leftControl2, 255);
    analogWrite(rightControl1, 0);
    analogWrite(rightControl2, 255);
    
    delay(30);
  }
}
