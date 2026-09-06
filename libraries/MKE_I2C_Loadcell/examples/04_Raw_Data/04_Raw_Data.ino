/*
  Example 04: Raw Data Reading
  
  Description:
  Reads the raw ADC value before any calibration factor is applied.
  This feature is highly useful for debugging, detecting sensor noise,
  hardware troubleshooting, or implementing custom calculation algorithms.

  Notes on Loadcell Types:
  - The amplitude of RAW value fluctuations (noise) heavily depends on the load cell's capacity.
  - A 20kg load cell will naturally have a much larger RAW noise amplitude than a 1kg load cell when unloaded.
*/

#include <Wire.h>
#include "MKE_I2C_Loadcell.h"

MKE_I2C_Loadcell scale;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!scale.begin()) {
    Serial.println(F("I2C Loadcell not found. Please check connections!"));
    while (1) delay(100);
  }
  
  Serial.println(F("I2C Loadcell connected successfully!"));
  
  // Optional: You can tare before reading Raw data, or skip it
  // scale.tare(); 
}

void loop() {
  // Read the raw signal (ADC value) from the HX710B processor via I2C
  int32_t rawValue = scale.getRawValue();
  
  // Print to the screen for graphing (Use Arduino IDE's Serial Plotter)
  Serial.print(F("Raw_Value:"));
  Serial.println(rawValue);
  
  // Faster sampling rate for smoother graphing
  delay(100); 
}
