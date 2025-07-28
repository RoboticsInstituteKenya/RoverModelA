#include "vehicle.hpp"

Motors::Motors(int enaPin, int in1Pin, int in2Pin, int enbPin, int in3Pin,
               int in4Pin)
    : _enaPin(enaPin), _in1Pin(in1Pin), _in2Pin(in2Pin), _enbPin(enbPin),
      _in3Pin(in3Pin), _in4Pin(in4Pin) {
  // Pin Direction
  pinMode(_enaPin, OUTPUT);
  pinMode(_in1Pin, OUTPUT);
  pinMode(_in2Pin, OUTPUT);
  pinMode(_enbPin, OUTPUT);
  pinMode(_in3Pin, OUTPUT);
  pinMode(_in4Pin, OUTPUT);
}

void Motors::run() {
  digitalWrite(_enaPin, _leftSpeed);
  digitalWrite(_enbPin, _rightSpeed);
}

void Motors::turnRight(int speed) {
  setSpeed(LEFT_MOTOR, 0);
  setSpeed(RIGHT_MOTOR, speed);
  setDirection(LEFT_MOTOR, false);
  setDirection(RIGHT_MOTOR, true);
  run();
}

void Motors::turnLeft(int speed) {
  setSpeed(LEFT_MOTOR, speed);
  setSpeed(RIGHT_MOTOR, 0);
  setDirection(LEFT_MOTOR, true);
  setDirection(RIGHT_MOTOR, false);
  run();
}

void Motors::forward(int speed) {
  setSpeed(LEFT_MOTOR, speed);
  setSpeed(RIGHT_MOTOR, speed);
  setDirection(LEFT_MOTOR, true);
  setDirection(RIGHT_MOTOR, true);
  run();
}

void Motors::backward(int speed) {
  setSpeed(LEFT_MOTOR, speed);
  setSpeed(RIGHT_MOTOR, speed);
  setDirection(LEFT_MOTOR, false);
  setDirection(RIGHT_MOTOR, false);
  run();
}

void Motors::setSpeed(MotorSide side, int speed) {
  if (side == LEFT_MOTOR)
    _leftSpeed = speed;
  else if (side == RIGHT_MOTOR)
    _rightSpeed = speed;
}

void Motors::setDirection(MotorSide side, bool forward) {
  if (side == LEFT_MOTOR) {
    digitalWrite(_in1Pin, forward ? HIGH : LOW);
    digitalWrite(_in2Pin, forward ? LOW : HIGH);
  } else if (side == RIGHT_MOTOR) {
    digitalWrite(_in3Pin, forward ? HIGH : LOW);
    digitalWrite(_in4Pin, forward ? LOW : HIGH);
  }
}

void Motors::stop() {
  _leftSpeed = 0;
  digitalWrite(_in1Pin, LOW);
  digitalWrite(_in2Pin, LOW);

  _rightSpeed = 0;
  digitalWrite(_in3Pin, LOW);
  digitalWrite(_in4Pin, LOW);

  run();
}

// ========================= SONAR =========================

Sonar::Sonar(int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;

  _sonar = new NewPing(_trigPin, _echoPin, ROVER_MAX_DISTANCE_CM);
}

long Sonar::getDistanceCM() {
  unsigned long dist = _sonar->ping_cm();

  Serial.print("Distance: ");
  Serial.print(dist);
  Serial.println(" cm");
  
  return (dist == 0) ? -1 : dist;
}
