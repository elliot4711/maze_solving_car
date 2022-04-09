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
const int leftMin = 140;

#define MAX_DISTANCE 50
#define STOP_DISTANCE 21

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

  Serial.println("front");
  Serial.println(front);
  Serial.println("right");
  Serial.println(right);
  Serial.println("left");
  Serial.println(left);

  if (left > 2350){ // 2060
    int startTime = millis();
    int time = millis();
    int duration = time - startTime;
    while (duration < 175){
      left = sonarLeft.ping();
      if (left == 0) {
        left = 2940;
      }
      front = sonarFront.ping();
      if (front == 0) {
        front = 2940;
      }
      error = 529 - left;
      P = error;
      I = I + error;
      D = error - lastError;
      lastError = error;
      motorspeed = P*Kp + I*Ki + D*Kd;

      if (front < 353) {
        motorspeed = motorspeed * 2;
      }

      speedRight = rightStandard - (motorspeed);
      speedLeft = leftStandard + motorspeed;
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
      delay(30);
    }
  }

  if (right > 2350){ // 2060
    int startTime = millis();
    int time = millis();
    int duration = time - startTime;
    while (duration < 175){
      right = sonarRight.ping();
      if (right == 0) {
        right = 2940;
      }
      front = sonarFront.ping();
      if (front == 0) {
        front = 2940;
      }
      error = right - 529;
      P = error;
      I = I + error;
      D = error - lastError;
      lastError = error;
      motorspeed = P*Kp + I*Ki + D*Kd;

      if (front < 353) {
        motorspeed = motorspeed * 2;
      }

      speedRight = rightStandard - (motorspeed);
      speedLeft = leftStandard + motorspeed;
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
      delay(30);
    }
  }

  else{
    error = right - left;

    P = error;
    I = I + error;
    D = error - lastError;
    lastError = error;
    motorspeed = P*Kp + I*Ki + D*Kd;
  
    speedRight = rightStandard - (motorspeed);
    speedLeft = leftStandard + motorspeed;
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
