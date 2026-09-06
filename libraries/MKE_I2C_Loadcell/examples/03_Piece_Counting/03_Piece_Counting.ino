/*
  Example 03: Piece Counting
  
  Description:
  Application of the PCS (Piece Counting System) feature to count the quantity 
  of identical objects (e.g., counting screws, beads, components...).

  Notes on Loadcell Types:
  - If the objects to be counted are very light (e.g., a 4.5g screw), you MUST use a low capacity load cell (1kg, 2kg, 5kg).
  - Using a 20kg load cell to count objects weighing a few grams will result in counting errors due to natural physical noise (~0.5g).
*/

#include <Wire.h>
#include "MKE_I2C_Loadcell.h"

MKE_I2C_Loadcell scale;

// To accurately count pieces, we need to know the weight of a single item.
// The best way to do this is to weigh a sample of multiple items and divide by the quantity.
// Example: You place 10 screws on a separate accurate scale (or use this scale via 01_Read_Weight)
// and find they weigh 45.0 grams in total.
const float SAMPLE_TOTAL_WEIGHT_GRAM = 45.0; // Total weight of the sample
const int SAMPLE_QUANTITY = 10;              // Number of items in the sample

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!scale.begin()) {
    Serial.println(F("I2C Loadcell not found. Please check connections!"));
    while (1) delay(100);
  }
  
  Serial.println(F("I2C Loadcell connected successfully!"));
  
  // Step 1: Tare the empty container/tray
  Serial.println(F("Taring empty container..."));
  scale.tare();
  delay(1000);
  
  // Step 2: Calculate and set the weight of a single item
  float singleItemWeight = SAMPLE_TOTAL_WEIGHT_GRAM / SAMPLE_QUANTITY;
  
  Serial.print(F("Setting single item weight to: "));
  Serial.print(singleItemWeight, 3);
  Serial.println(F(" g"));
  
  scale.setPieceWeight(singleItemWeight);
  
  Serial.println(F("\n== PLEASE ADD ITEMS TO THE TRAY (E.G., SCREWS) =="));
  Serial.println(F("To increase accuracy, add more items and type 'u' (Update) to auto-refine the sample."));
  Serial.println(F("Type 't' (Tare) to zero the scale."));
}

void loop() {
  if (Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'u' || cmd == 'U') {
      scale.autoRefinePieceWeight();
      Serial.println(F("\n>>> SUCCESS: Sample weight has been AUTO-REFINED based on current count!"));
    } else if (cmd == 't' || cmd == 'T') {
      scale.tare();
      Serial.println(F("\n>>> SUCCESS: Scale has been TARED!"));
    }
  }

  // Get total weight
  float totalWeight = scale.getGram();
  
  // Count the number of pieces (PCS)
  int32_t totalPieces = scale.getPCS();
  
  Serial.print(F("Total weight: "));
  Serial.print(totalWeight, 1);
  Serial.print(F(" g \t| "));
  
  Serial.print(F("Piece Count (PCS): "));
  Serial.print(totalPieces);
  Serial.println(F(" pcs"));
  
  delay(500);
}
