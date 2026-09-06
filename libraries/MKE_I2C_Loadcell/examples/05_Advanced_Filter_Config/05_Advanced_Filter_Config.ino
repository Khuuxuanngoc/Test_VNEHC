#include "MKE_I2C_Loadcell.h"
#include <Wire.h>

MKE_I2C_Loadcell scale;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(2000);

  Serial.println(F("===================================="));
  Serial.print(F("FIRMWARE VERSION: "));
  Serial.println(scale.getFirmwareVersion());
  Serial.println(F("===================================="));

  delay(2000); // Wait 2 seconds

  Serial.println("\n=== Advanced Filter Config ===");

  if (!scale.begin()) {
    Serial.println("Loadcell not found! Please check connections.");
    while(1);
  }

  // --- Configure Filter Level (Kalman Filter Level) ---
  // 0: Raw (No filter), 1: Fast, 2: Medium (Default), 3: Slow (High stability)
  Serial.println("\n--- Configuring Filter Level ---");
  Serial.println("Setting Filter Level to 3 (Slow / Super Stable)");
  scale.setFilterLevel(3);
  delay(50); // Mandatory delay after SET command to allow I2C Slave to save to EEPROM
  Serial.print("Current Filter Level: ");
  Serial.println(scale.getFilterLevel());

  Serial.println("\nConfiguration DONE! The module will remember these settings.");
  Serial.println("Press firmly to see the stable response of Filter Level 3.\n");

  // You can Tare once in setup if you want an initial zero point
  scale.tare();
}

void loop() {
  // Read the filtered value
  Serial.print("Weight (g): ");
  Serial.println(scale.getGram(), 2);
  delay(500);
}
