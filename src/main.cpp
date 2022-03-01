#include <Arduino.h>

//Motor control pins
const int leftMotorVelocity = 10;
const int rightMotorVelocity = 9;

const int leftControl1 = 7;
const int leftControl2 = 6;

const int rightControl1 = 5;
const int rightControl2 = 4;

//Ultrasonic sensor pins
const int trigFront = A0;
const int echoFront = A1;

const int trigRight = A2;
const int echoRight = A3;

const int trigLeft = A4;
const int echoLeft = A5;




void setup() 
{
  Serial.begin(9600); //Initialises serial connection 

  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);

  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);

  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);

  pinMode(leftMotorVelocity, OUTPUT);
  pinMode(rightMotorVelocity, OUTPUT);

  pinMode(leftControl1, OUTPUT);
  pinMode(leftControl2, OUTPUT);
  pinMode(rightControl1, OUTPUT);
  pinMode(rightControl2, OUTPUT);
  
  delay(10000);
}

void driveRight()
{
  analogWrite(leftMotorVelocity, 120);
  analogWrite(rightMotorVelocity, 120);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 255);
  analogWrite(rightControl2, 0);
  delay(700);
}

void driveLeft()
{
  analogWrite(leftMotorVelocity, 120);
  analogWrite(rightMotorVelocity, 120);

  analogWrite(leftControl1, 0);
  analogWrite(leftControl2, 255);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);
  delay(700);
}

void reverse()
{
  analogWrite(leftMotorVelocity, 120);
  analogWrite(rightMotorVelocity, 120);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 255);
  analogWrite(rightControl2, 0);
  delay(1200);
}

void loop() 
{
  long timeFront, timeLeft, timeRight, right, left, front;

  digitalWrite(trigFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigFront, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigFront, LOW);
  timeFront = pulseIn(echoFront, HIGH);
  front = timeFront/29/2;


  digitalWrite(trigLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigLeft, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigLeft, LOW);
  timeLeft = pulseIn(echoLeft, HIGH);
  left = timeLeft/29/2;

  digitalWrite(trigRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigRight, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigRight, LOW);
  timeRight = pulseIn(echoRight, HIGH);
  right = timeRight/29/2;

  analogWrite(leftMotorVelocity, 0);
  analogWrite(rightMotorVelocity, 0);

  analogWrite(leftControl1, 255);
  analogWrite(leftControl2, 0);
  analogWrite(rightControl1, 0);
  analogWrite(rightControl2, 255);

  if (front > 8)
  {
    if (right > 7 && right < 13)
    {
      analogWrite(leftMotorVelocity, 120);
      analogWrite(rightMotorVelocity, 150);

      analogWrite(leftControl1, 255);
      analogWrite(leftControl2, 0);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }
    
    if (right >= 13)
    {
      analogWrite(leftMotorVelocity, 255);
      analogWrite(rightMotorVelocity, 60);

      analogWrite(leftControl1, 255);
      analogWrite(leftControl2, 0);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }

    if (right <= 7)
    {
      analogWrite(leftMotorVelocity, 60);
      analogWrite(rightMotorVelocity, 255);

      analogWrite(leftControl1, 255);
      analogWrite(leftControl2, 0);
      analogWrite(rightControl1, 0);
      analogWrite(rightControl2, 255);
    }
  }

  if (left <= 20 && right > 20 && front <= 8) driveRight();

  if (left > 20 && right > 20 && front <= 8) driveRight();

  if (right <= 20 && left > 20 && front <= 8) driveLeft();
  
  if (right <= 20 && left <= 20 && front <= 8) reverse();
  
}

