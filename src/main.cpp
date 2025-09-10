#include "Vehicle.hpp"
#include <Arduino.h>

// Create Vehicle and UltrasonicSensor objects with defined pin configurations
Vehicle vehicle(L298N_ENA_PIN, L298N_IN1_PIN, L298N_IN2_PIN, L298N_ENB_PIN,
                L298N_IN3_PIN, L298N_IN4_PIN);
UltrasonicSensor ultrasonic(ULTRASONIC_TRIG_PIN, ULTRASONIC_ECHO_PIN,
                            ULTRASONIC_MAX_DISTANCE);

void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  DEBUG_PRINTLN("Debugging enabled");
#endif
  vehicle.stop(); // Ensure the vehicle is stopped at startup
}
void loop() {
  unsigned int distance = ultrasonic.getDistance();
  DEBUG_PRINT("Distance: ");
  DEBUG_PRINT(distance);
  DEBUG_PRINTLN(" cm");

  if (distance < 50) {
    vehicle.stop();
    delay(1000);
    vehicle.moveBackward(150);
    delay(1000);
    vehicle.stop();
    delay(500);
    vehicle.turnRight(150);
    delay(500);
    vehicle.stop();
    delay(1000);
  } else {
    vehicle.moveForward(200);
  }

  delay(100);
}