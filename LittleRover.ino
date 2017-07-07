#include <Servo.h>
int distance = A0;
int led1 = 8, led2 = 9;
Servo leftPower;
Servo rightPower;
unsigned long time;
bool on = false;
float obstacleDist = 0.0f;

void setup() {
  Serial.begin(115200);
  leftPower.attach(3);
  rightPower.attach(5);
  leftPower.write(90);
  rightPower.write(90);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  LEDs();
  float reading1 = TakeReading();
  float reading2 = TakeReading();
  Serial.println(reading1);
  Serial.println(reading2);
  obstacleDist = reading1 >= reading2 ? reading1 : reading2;
  if(obstacleDist < 10.0f){
    Serial.println("turn");
    turn();
  }else{
    Serial.println("forward");
    forward();
  }
}

void LEDs(){
  if(millis() - time > 1000)
    time = millis();
    
  if(millis() - time < 500){
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }else if(millis() - time > 500){
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
}

void forward(){
  leftPower.write(135);
  rightPower.write(45);
}

void turn(){
  leftPower.write(90);
  rightPower.write(45);
}

float TakeReading(){
  unsigned long echo = 0;
  float result = 0.0f;
  pinMode(distance, OUTPUT);  
  digitalWrite(distance, LOW);
  delayMicroseconds(2);
  digitalWrite(distance, HIGH);
  delayMicroseconds(5);
  digitalWrite(distance, LOW);

  pinMode(distance, INPUT);
  digitalWrite(distance, HIGH);
  echo = pulseIn(distance,HIGH,38000);
  result = echo/58.138;
  
  return result;
}
