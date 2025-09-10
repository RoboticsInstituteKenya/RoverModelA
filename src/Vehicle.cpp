#include "Vehicle.hpp"

Vehicle::Vehicle(int enPin, int in1Pin, int in2Pin, int en2Pin, int in3Pin,
                 int in4Pin)
    : _enAPin(enPin), _in1Pin(in1Pin), _in2Pin(in2Pin), _enBPin(en2Pin),
      _in3Pin(in3Pin), _in4Pin(in4Pin) {
  pinMode(_enAPin, OUTPUT);
  pinMode(_in1Pin, OUTPUT);
  pinMode(_in2Pin, OUTPUT);
  pinMode(_enBPin, OUTPUT);
  pinMode(_in3Pin, OUTPUT);
  pinMode(_in4Pin, OUTPUT);
}

void Vehicle::moveForward(int speed) {
  analogWrite(_enAPin, speed);
  digitalWrite(_in1Pin, HIGH);
  digitalWrite(_in2Pin, LOW);

  analogWrite(_enBPin, speed);
  digitalWrite(_in3Pin, HIGH);
  digitalWrite(_in4Pin, LOW);
}

void Vehicle::moveBackward(int speed) {
  analogWrite(_enAPin, speed);
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, HIGH);

  analogWrite(_enBPin, speed);
  digitalWrite(_in3Pin, LOW);
  digitalWrite(_in4Pin, HIGH);
}

void Vehicle::turnLeft(int speed) {
  analogWrite(_enAPin, speed);
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, HIGH);

  analogWrite(_enBPin, speed);
  digitalWrite(_in3Pin, HIGH);
  digitalWrite(_in4Pin, LOW);
}

void Vehicle::turnRight(int speed) {
  analogWrite(_enAPin, speed);
  digitalWrite(_in1Pin, HIGH);
  digitalWrite(_in2Pin, LOW);

  analogWrite(_enBPin, speed);
  digitalWrite(_in3Pin, LOW);
  digitalWrite(_in4Pin, HIGH);
}

void Vehicle::stop() {
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);
  digitalWrite(_in3Pin, LOW);
  digitalWrite(_in4Pin, LOW);

  analogWrite(_enAPin, 0);
  analogWrite(_enBPin, 0);
}

// UltrasonicSensor class implementation
UltrasonicSensor::UltrasonicSensor(int trigPin, int echoPin,
                                   unsigned int maxDistance)
    : _trigPin(trigPin), _echoPin(echoPin), _maxDistance(maxDistance) {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

unsigned int UltrasonicSensor::getDistance() {
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  unsigned long distance = pulseIn(_echoPin, HIGH) / 58;

  DEBUG_PRINT("Raw distance: ");
  DEBUG_PRINT(distance);
  DEBUG_PRINTLN(" cm");
  if (distance > _maxDistance) {
    distance = _maxDistance;
  }

  return distance;
}
