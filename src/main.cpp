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

#define MAX_DISTANCE 200
#define STOP_DISTANCE 21
#define STOP_DELAY 250
#define TURN_DELAY 75

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

// void driveRight()
// {
//   analogWrite(leftMotorVelocity, 0);
//   analogWrite(rightMotorVelocity, 0);

//   delay(STOP_DELAY);

//   analogWrite(leftMotorVelocity, leftStandard);
//   analogWrite(rightMotorVelocity, rightStandard);

//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 255);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 0);

//   delay(300);
  
//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 0);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 0);

//   delay(STOP_DELAY);

//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 255);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 255);

//   int right;
//   right = sonarRight.ping_cm();
//   if (right == 0) {
//     right = MAX_DISTANCE;
//   }

//   while (right > 20) {
//   right = sonarRight.ping_cm();
//   if (right == 0) {
//     right = MAX_DISTANCE;
//   }
//   delay(30);
//   }

// }

// void driveLeft()
// {
//   analogWrite(leftMotorVelocity, 0);
//   analogWrite(rightMotorVelocity, 0);

//   delay(STOP_DELAY);

//   analogWrite(leftMotorVelocity, leftStandard);
//   analogWrite(rightMotorVelocity, rightStandard);

//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 0);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 255);
//   delay(300);
  
//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 0);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 0);

//   delay(STOP_DELAY);
  
//   analogWrite(leftControl1, 0);
//   analogWrite(leftControl2, 255);
//   analogWrite(rightControl1, 0);
//   analogWrite(rightControl2, 255);
  
//   int left;
//   left = sonarLeft.ping_cm();
//   if (left == 0) {
//     left = MAX_DISTANCE;
//   }

//   while (left > 20) {
//     left = sonarLeft.ping_cm();
//     if (left == 0) {
//     left = MAX_DISTANCE;
//     }
//     delay(30);
//   }

// }

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

void driveRight(){
  int oldFront, oldRight, newLeft, newFront, rightFront, frontLeft;
  oldFront = sonarFront.ping_cm();
  oldRight = sonarRight.ping_cm();

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(250);

  analogWrite(leftMotorVelocity, 150);
  analogWrite(rightMotorVelocity, 150);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 255);
  analogWrite(rightControl2, 0);

  delay(50);

  newLeft = sonarLeft.ping_cm();
  newFront = sonarFront.ping_cm();

  rightFront = oldRight - newFront;
  frontLeft = oldFront - newLeft;

  while (rightFront > 1 || rightFront < -1){

    analogWrite(leftMotorVelocity, 150);
    analogWrite(rightMotorVelocity, 150);

    analogWrite(leftControl1, 0);
    analogWrite(leftControl2, 255);
    analogWrite(rightControl1, 255);
    analogWrite(rightControl2, 0);

    newLeft = sonarLeft.ping_cm();
    newFront = sonarFront.ping_cm();

    rightFront = oldRight - newFront;
    frontLeft = oldFront - newLeft;

    if (frontLeft < 1 && frontLeft > -1) {
      break;
    }
    delay(25);
  }

  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 0);

  delay(200);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  delay(600);

}

void driveLeft(){
  int oldFront, oldLeft, newRight, newFront, leftFront, frontRight;
  oldFront = sonarFront.ping_cm();
  oldLeft = sonarLeft.ping_cm();

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  delay(250);

  analogWrite(leftMotorVelocity, 150);
  analogWrite(rightMotorVelocity, 150);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  delay(50);

  newRight = sonarRight.ping_cm();
  newFront = sonarFront.ping_cm();

  leftFront = oldLeft - newFront;
  frontRight = oldFront - newRight;

  while (leftFront > 1 || leftFront < -1){
    analogWrite(leftMotorVelocity, 150);
    analogWrite(rightMotorVelocity, 150);

    analogWrite(leftControl1, 255);
    analogWrite(leftControl2, 0);
    analogWrite(rightControl1, 0);
    analogWrite(rightControl2, 255);

    newRight = sonarRight.ping_cm();
    newFront = sonarFront.ping_cm();

    leftFront = oldLeft - newFront;
    frontRight = oldFront - newRight;

    if (frontRight < 1 && frontRight > -1) {
      break;
    }
    delay(25);
  }
 
  analogWrite(leftMotorVelocity, leftStandard);
  analogWrite(rightMotorVelocity, rightStandard);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 0);

  delay(200);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

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
      delay(TURN_DELAY);
      driveRight();
    }

    if (left >= 40)
    {
      delay(TURN_DELAY);
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

