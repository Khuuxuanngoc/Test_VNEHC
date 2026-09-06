/*
  Example 08: Multiple Loadcells
  
  Description:
  Demonstrates how to connect and read from two or more MKE I2C Loadcell 
  modules on the same I2C bus. You MUST change the I2C address of one of 
  the modules (e.g., using Example 07) before running this code.
  
  Hardware Connections:
  - VCC  -> 5V (or 3.3V depending on the microcontroller)
  - GND  -> GND
  - SCL  -> SCL (E.g., A5 on Arduino Uno)
  - SDA  -> SDA (E.g., A4 on Arduino Uno)
  * Connect all modules in parallel to the same I2C bus.
*/

#include <Wire.h>
#include "MKE_I2C_Loadcell.h"

// Initialize two loadcell objects
MKE_I2C_Loadcell scale1; // We will use default address 0x0A
MKE_I2C_Loadcell scale2; // We will use a changed address 0x0B

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  Serial.println(F("Initializing Loadcells..."));
  
  // Initialize scale 1 (default address 0x0A)
  if (!scale1.begin(0x0A)) {
    Serial.println(F("Loadcell 1 (0x0A) not found."));
  } else {
    Serial.println(F("Loadcell 1 (0x0A) connected!"));
  }
  
  // Initialize scale 2 (changed address 0x0B)
  if (!scale2.begin(0x0B)) {
    Serial.println(F("Loadcell 2 (0x0B) not found. Did you change its address?"));
  } else {
    Serial.println(F("Loadcell 2 (0x0B) connected!"));
  }
}

void loop() {
  // Read weight from scale 1
  float weight1 = scale1.getGram();
  
  // Read weight from scale 2
  float weight2 = scale2.getGram();
  
  // Print to Serial Monitor
  Serial.print(F("Scale 1 (0x0A): "));
  Serial.print(weight1, 1);
  Serial.print(F(" g \t| "));
  
  Serial.print(F("Scale 2 (0x0B): "));
  Serial.print(weight2, 1);
  Serial.println(F(" g"));
  
  delay(500); // Wait half a second before reading again
}
