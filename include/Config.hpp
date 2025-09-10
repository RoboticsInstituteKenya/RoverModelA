#pragma once

#include <Arduino.h>

// Debugging Configuration settings
#define DEBUG 1
#define DEBUG_PRINT(x)                                                         \
  if (DEBUG)                                                                   \
    Serial.print(x);
#define DEBUG_PRINTLN(x)                                                       \
  if (DEBUG)                                                                   \
    Serial.println(x);

// L298N Configuration settings
#define L298N_ENA_PIN 6
#define L298N_IN1_PIN 4
#define L298N_IN2_PIN 5
#define L298N_ENB_PIN 3
#define L298N_IN3_PIN 8
#define L298N_IN4_PIN 7

// Ultrasonic Sensor Configuration settings
#define ULTRASONIC_MAX_DISTANCE 400
#define ULTRASONIC_TRIG_PIN 10
#define ULTRASONIC_ECHO_PIN 9