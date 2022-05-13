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
const int leftMin = 120;
int old1Left = 0;
int old1Right = 0;
int old1Front = 0;
int old2Front = 0;
int old2Left = 0;
int old2Right = 0;
int lastTime = 0;

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
  int right, left, front, speedRight, speedLeft, error, correction, leftError, rightError, checkTime;
  
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
    long startTime = millis();
    long time = millis();
    long duration = time - startTime;
    analogWrite(leftMotorVelocity, 255);
    analogWrite(rightMotorVelocity, 100);
    delay(50);
    
    while (right > 1058 || left > 1058){
      right = sonarRight.ping();
      if (right == 0) {
        right = 2940;
      }
      front = sonarFront.ping();
      if (front == 0) {
        front = 2940;
      }
      left = sonarLeft.ping();
      if (left == 0) {
        left = 2940;
      }

      if (abs(front-old1Front) < 3){
        if (abs(left - old1Left) < 3){
          if (abs(right- old1Right) < 3){
            if (abs(old1Front - old2Front) < 3){
              if (abs(old1Left - old2Left) < 3){
                if (abs(old1Right - old2Right) < 3){
                  checkTime = millis();
                  if ((checkTime > 8000) && ((checkTime - lastTime) > 3000)){
                    analogWrite(leftMotorVelocity, 255);
                    analogWrite(rightMotorVelocity, 255);

                    analogWrite(leftControl1, 255);
                    analogWrite(leftControl2, 0);
                    analogWrite(rightControl1, 255);
                    analogWrite(rightControl2, 0);
                    
                    delay(500);

                    analogWrite(leftControl1, 0);
                    analogWrite(leftControl2, 255);
                    analogWrite(rightControl1, 0);
                    analogWrite(rightControl2, 255);

                    if (right > 1176){
                      analogWrite(leftMotorVelocity, 255);
                      analogWrite(rightMotorVelocity, 100);
                      delay(500);

                    }
                    else{
                      analogWrite(leftMotorVelocity, 100);
                      analogWrite(rightMotorVelocity, 255);
                      delay(500);
                    }

                    old1Left = 0;
                    old1Right = 0;
                    old1Front = 0;
                    old2Front = 0;
                    old2Left = 0;
                    old2Right = 0;

                    lastTime = millis();

                    break;
                  }
                }
              }
            }
          }
        }
      }

      rightError = (right - 647)*2;
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
      if (duration > 3000){
        break;
      }

      old1Left = left;
      old1Right = right;
      old1Front = front;
      old2Left = old1Left;
      old2Right = old1Right;
      old2Front = old1Front;

      delay(15);
    }
  }

  else if (left > 2059){
    long startTime = millis();
    long time = millis();
    long duration = time - startTime;
    analogWrite(leftMotorVelocity, 80);
    analogWrite(rightMotorVelocity, 255);
    delay(50);

    while (right > 1058 || left > 1058){
      right = sonarRight.ping();
      if (right == 0) {
        right = 2940;
      }
      front = sonarFront.ping();
      if (front == 0) {
        front = 2940;
      }
      left = sonarLeft.ping();
      if (left == 0) {
        left = 2940;
      }

      if (abs(front-old1Front) < 3){
        if (abs(left - old1Left) < 3){
          if (abs(right- old1Right) < 3){
            if (abs(old1Front - old2Front) < 3){
              if (abs(old1Left - old2Left) < 3){
                if (abs(old1Right - old2Right) < 3){
                  checkTime = millis();
                  if ((checkTime > 8000) && ((checkTime - lastTime) > 3000)){
                    analogWrite(leftMotorVelocity, 255);
                    analogWrite(rightMotorVelocity, 255);

                    analogWrite(leftControl1, 255);
                    analogWrite(leftControl2, 0);
                    analogWrite(rightControl1, 255);
                    analogWrite(rightControl2, 0);
                    
                    delay(500);

                    analogWrite(leftControl1, 0);
                    analogWrite(leftControl2, 255);
                    analogWrite(rightControl1, 0);
                    analogWrite(rightControl2, 255);

                    if (right > 1176){
                      analogWrite(leftMotorVelocity, 255);
                      analogWrite(rightMotorVelocity, 100);
                      delay(500);

                    }
                    else{
                      analogWrite(leftMotorVelocity, 100);
                      analogWrite(rightMotorVelocity, 255);
                      delay(500);           
                    }

                    old1Left = 0;
                    old1Right = 0;
                    old1Front = 0;
                    old2Front = 0;
                    old2Left = 0;
                    old2Right = 0;

                    lastTime = millis();

                    break;
                  }
                }
              }
            }
          }
        }
      }
      
      leftError = (647 - left)*2;
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
      if (duration > 3000){
        break;
      }

      old1Left = left;
      old1Right = right;
      old1Front = front;
      old2Left = old1Left;
      old2Right = old1Right;
      old2Front = old1Front;

      delay(15);
    }
  }

  else{

    if (abs(front-old1Front) < 3){
      if (abs(left - old1Left) < 3){
        if (abs(right- old1Right) < 3){
          if (abs(old1Front - old2Front) < 3){
            if (abs(old1Left - old2Left) < 3){
              if (abs(old1Right - old2Right) < 3){
                checkTime = millis();
                if ((checkTime > 8000) && ((checkTime - lastTime) > 3000)){
                  analogWrite(leftMotorVelocity, 255);
                  analogWrite(rightMotorVelocity, 255);

                  analogWrite(leftControl1, 255);
                  analogWrite(leftControl2, 0);
                  analogWrite(rightControl1, 255);
                  analogWrite(rightControl2, 0);
                  
                  delay(500);

                  analogWrite(leftControl1, 0);
                  analogWrite(leftControl2, 255);
                  analogWrite(rightControl1, 0);
                  analogWrite(rightControl2, 255);

                  if (right > 1176){
                    analogWrite(leftMotorVelocity, 255);
                    analogWrite(rightMotorVelocity, 100);
                    delay(500);

                  }
                  else{
                    analogWrite(leftMotorVelocity, 100);
                    analogWrite(rightMotorVelocity, 255);
                    delay(500);
                  }

                  old1Left = 0;
                  old1Right = 0;
                  old1Front = 0;
                  old2Front = 0;
                  old2Left = 0;
                  old2Right = 0;

                  lastTime = millis();
                }
              }
            }
          }
        }
      }
    }
    
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
    
    delay(15);
  }
  old1Left = left;
  old1Right = right;
  old1Front = front;
  old2Left = old1Left;
  old2Right = old1Right;
  old2Front = old1Front;
}
