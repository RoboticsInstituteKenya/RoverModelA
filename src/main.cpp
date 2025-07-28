#include <Arduino.h>

#include "config.hpp"
#include "vehicle.hpp"

Motors motors(ROVER_ENA_PIN, ROVER_IN1_PIN, ROVER_IN2_PIN, ROVER_ENB_PIN,
              ROVER_IN3_PIN, ROVER_IN4_PIN);
Sonar sonar(ROVER_SONAR_TRIG_PIN, ROVER_SONAR_ECHO_PIN);

void setup() {
  Serial.begin(115200);
  Serial.println("Rover Model A - Starting...");

  pinMode(LED_BUILTIN, OUTPUT); // Ensure LED_BUILTIN is set as an output
  randomSeed(analogRead(A0));   // Seed the random number generator
}

void loop() {
  long distance = sonar.getDistanceCM();

  if (distance <= 0 || distance < ROVER_TURNING_DISTANCE) {
    motors.stop();

    // Randomly choose left or right turn
    int turnDirection = random(2); // 0 for left, 1 for right

    // Turn until clear
    while (distance <= 0 || distance < ROVER_TURNING_DISTANCE) {
      if (turnDirection == 0)
        motors.turnLeft(ROVER_TURNING_SPEED);
      else
        motors.turnRight(ROVER_TURNING_SPEED);

      distance = sonar.getDistanceCM(); // Read distance again
    }

    motors.stop(); // Stop turning once clear
    delay(1000);
  } else {
    motors.forward(ROVER_MOVING_SPEED); // Move forward if no obstacle
  }
}
