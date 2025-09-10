#pragma once

#include "Config.hpp"
#include <NewPing.h>

class Vehicle {
public:
  Vehicle(int enPin, int in1Pin, int in2Pin, int en2Pin, int in3Pin,
          int in4Pin);
  void moveForward(int speed);
  void moveBackward(int speed);
  void turnLeft(int speed);
  void turnRight(int speed);
  void stop();

private:
  int _enAPin;
  int _in1Pin;
  int _in2Pin;
  int _enBPin;
  int _in3Pin;
  int _in4Pin;
};

class UltrasonicSensor {
public:
  UltrasonicSensor(int trigPin, int echoPin,
                   unsigned int maxDistance = ULTRASONIC_MAX_DISTANCE);
  unsigned int getDistance();

private:
  int _trigPin;
  int _echoPin;
  unsigned int _maxDistance;
};
