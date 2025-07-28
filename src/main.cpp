#include <Arduino.h>

#include "config.hpp"
#include "vehicle.hpp"

Motors motors(ROVER_ENA_PIN, ROVER_IN1_PIN, ROVER_IN2_PIN, ROVER_ENB_PIN,
              ROVER_IN3_PIN, ROVER_IN4_PIN);
Sonar sonar(ROVER_SONAR_TRIG_PIN, ROVER_SONAR_ECHO_PIN);

int distance;
long duration;
bool isMoving = false;
unsigned long lastStartMovingTime = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Rover Model A - Starting...");

  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(A0));
}

void loop() {
  delay(100);
  digitalWrite(ROVER_SONAR_TRIG_PIN, LOW);
  delayMicroseconds(10);

  digitalWrite(ROVER_SONAR_TRIG_PIN, HIGH);
  delayMicroseconds(2);

  digitalWrite(ROVER_SONAR_TRIG_PIN, LOW);

  duration = pulseIn(ROVER_SONAR_ECHO_PIN, HIGH);
  distance = duration * 0.0344 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < ROVER_TURNING_DISTANCE) {
    motors.stop();
    Serial.println("Stopped due to obstacle.");
    delay(500);
    motors.turnRight(ROVER_TURNING_SPEED);
    isMoving = true;
    lastStartMovingTime = millis();
    Serial.println("Turning right due to obstacle.");
    delay(500);
  } else {
    if (!isMoving || (millis() - lastStartMovingTime > 500)) {
      motors.forward(ROVER_MOVING_SPEED);
      isMoving = true;
      lastStartMovingTime = millis();
      Serial.println("Moving forward.");
    }
  }
}