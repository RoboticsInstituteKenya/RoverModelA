#pragma once

#include "config.hpp"
#include <Arduino.h>
#include <NewPing.h>

typedef enum {
  LEFT_MOTOR,
  RIGHT_MOTOR,
} MotorSide;

class Motors {
private:
  int _enaPin;
  int _in1Pin;
  int _in2Pin;
  int _enbPin;
  int _in3Pin;
  int _in4Pin;

  int _leftSpeed = 0;
  int _rightSpeed = 0;

public:
  Motors(int enaPin, int in1Pin, int in2Pin, int enbPin, int in3Pin,
         int in4Pin);

  void setSpeed(MotorSide side, int speed);
  void setDirection(MotorSide side, bool forward);
  void stop();
  void run();
  void turnRight(int speed);
  void turnLeft(int speed);
  void forward(int speed) ;
  void backward(int speed);
};

// ========================= SONAR CLASS =========================
class Sonar {
private:
  NewPing *_sonar;
  int _trigPin;
  int _echoPin;

public:
  Sonar() = delete; // Default constructor is not allowed
  Sonar(int trigPin, int echoPin);
  long getDistanceCM();
};
