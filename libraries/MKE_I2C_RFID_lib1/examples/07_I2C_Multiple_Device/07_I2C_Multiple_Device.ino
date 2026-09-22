#include <Wire.h>
#include "MKE_I2C_RFID.h"

// Initialize 2 RFID objects for 2 modules with different addresses
MKE_I2C_RFID rfid1;
MKE_I2C_RFID rfid2;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println(F("========================================"));
  Serial.println(F(" MKE I2C RFID - Multiple Devices Test"));
  Serial.println(F("========================================"));

  // Initialize module 1 (Default address 0x29)
  if (rfid1.begin(0x29)) {
    Serial.println(F("Module 1 (0x29) Initialized!"));
  } else {
    Serial.println(F("Failed to find Module 1 at 0x29"));
  }

  // Initialize module 2 (Address has been changed to 0x30)
  // You need to run example 05_Change_I2C_Address to change one module's address to 0x30 first.
  if (rfid2.begin(0x30)) {
    Serial.println(F("Module 2 (0x30) Initialized!"));
  } else {
    Serial.println(F("Failed to find Module 2 at 0x30"));
  }
  
  Serial.println(F("Bring a card close to any module..."));
}

void printUID(uint8_t moduleNum, uint8_t* uid, uint8_t uidSize) {
  Serial.print(F("Module "));
  Serial.print(moduleNum);
  Serial.print(F(" detected Card UID: "));
  for (uint8_t i = 0; i < uidSize; i++) {
    if (uid[i] < 0x10) Serial.print(F("0"));
    Serial.print(uid[i], HEX);
    if (i < uidSize - 1) Serial.print(F(" "));
  }
  Serial.println();
}

void loop() {
  uint8_t uid[10];
  uint8_t uidSize;

  // Check for card at Module 1
  if (rfid1.isCardPresent()) {
    if (rfid1.getUID(uid, uidSize)) {
      printUID(1, uid, uidSize);
      rfid1.haltCard(); // Halt the card to prevent continuous polling
    }
  }

  // Wait a moment to avoid I2C bus congestion
  delay(50);

  // Check for card at Module 2
  if (rfid2.isCardPresent()) {
    if (rfid2.getUID(uid, uidSize)) {
      printUID(2, uid, uidSize);
      rfid2.haltCard();
    }
  }

  delay(50);
}
