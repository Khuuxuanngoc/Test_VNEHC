/*
  Example 01: Read Weight
  
  Description:
  The most basic code to connect to the MKE I2C Loadcell module and read the weight.
  Supports multiple units such as Grams, Kilograms, Ounces (Oz), Pounds (Lb), etc.
  
  Hardware Connections:
  - VCC  -> 5V (or 3.3V depending on the microcontroller)
  - GND  -> GND
  - SCL  -> SCL (E.g., A5 on Arduino Uno, 22 on ESP32)
  - SDA  -> SDA (E.g., A4 on Arduino Uno, 21 on ESP32)

  Notes on Loadcell Types:
  - This library supports all load cell capacities (1kg, 5kg, 10kg, 20kg...).
  - To accurately measure light objects (a few grams), you must use a low capacity load cell (1kg, 5kg).
  - High capacity load cells (20kg) always have a natural noise/drift around ~0.5g.
*/

#include <Wire.h>
#include "MKE_I2C_Loadcell.h"

MKE_I2C_Loadcell scale;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Initialize the connection with the I2C Loadcell. 
  // By default, it uses address 0x0A (10 in decimal).
  
  if (!scale.begin()) {
    Serial.println(F("I2C Loadcell not found. Please check connections!"));
    while (1) delay(100);
  }
  
  Serial.println(F("I2C Loadcell connected successfully!"));
  
  // You can Tare once in setup if you want an initial zero point
  // scale.tare(); 
}

void loop() {
  // 1. Read basic weight in Grams
  float weightGram = scale.getGram();
  
  // 2. Convert to other units
  float weightKg = scale.getKilogram();
  float weightOz = scale.getOunce();
  float weightLb = scale.getPound();
  float weightCarat = scale.getCarat();
  
  // Print to Serial Monitor
  Serial.print(F("Gram: "));
  Serial.print(weightGram, 1);
  Serial.print(F(" g \t| "));
  
  Serial.print(F("Kg: "));
  Serial.print(weightKg, 3);
  Serial.print(F(" kg \t| "));
  
  Serial.print(F("Oz: "));
  Serial.print(weightOz, 2);
  Serial.print(F(" oz \t| "));
  
  Serial.print(F("Carat: "));
  Serial.print(weightCarat, 2);
  Serial.println(F(" ct"));
  
  delay(500); // Wait half a second before reading again
}
