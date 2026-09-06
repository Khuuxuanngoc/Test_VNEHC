/*
 * 97_Factory_Auto_Test
 * 
 * FACTORY COMPREHENSIVE AUTOMATED TEST
 * 
 * This example is designed for manufacturers to run an automated PASS/FAIL 
 * test on the I2C Loadcell Module to ensure all commands, EEPROM read/writes, 
 * and sensors are working correctly before shipping.
 */

#include <Wire.h>
#include "MKE_I2C_Loadcell_Advanced.h"

MKE_I2C_Loadcell_Advanced scale;

int errorCount = 0;

void printResult(bool pass, const char* testName, const char* failReason = "", String actualValue = "") {
  Serial.print(F("["));
  if (pass) {
    Serial.print(F("PASS"));
  } else {
    Serial.print(F("FAIL"));
    errorCount++;
  }
  Serial.print(F("] "));
  Serial.print(testName);
  if (!pass) {
    if (failReason[0] != '\0') {
      Serial.print(F(" - Cause: "));
      Serial.print(failReason);
    }
    if (actualValue.length() > 0) {
      Serial.print(F(" | Actual: "));
      Serial.print(actualValue);
    }
  }
  Serial.println();
}

bool checkFloat(float expected, float actual) {
  return fabs(expected - actual) < 0.001;
}

void printMenu() {
  Serial.println(F("\n============================================="));
  Serial.println(F("     FACTORY COMPREHENSIVE AUTO TEST         "));
  Serial.println(F("============================================="));
  Serial.println(F("Commands:"));
  Serial.println(F(" 1 - Connection Test"));
  Serial.println(F(" 2 - Module Info Test"));
  Serial.println(F(" 3 - Admin Unlock Test"));
  Serial.println(F(" 4 - EEPROM Parameter R/W Test"));
  Serial.println(F(" 5 - Sensor Alive Test"));
  Serial.println(F(" 6 - Admin Lock Test"));
  Serial.println(F(" a - Test All"));
  Serial.println(F("============================================="));
  Serial.println(F("Send a command to run test..."));
}

void testConnection() {
  Serial.println(F("\n--- 1. CONNECTION TEST ---"));
  bool connected = scale.begin();
  printResult(connected, "I2C Connection OK", "I2C Loadcell Module not found!");
}

void testInfo() {
  Serial.println(F("\n--- 2. MODULE INFO TEST ---"));
  Serial.print(F("Firmware Version : ")); Serial.println(scale.getFirmwareVersion());
  Serial.print(F("Product Code     : ")); Serial.println(scale.getProductCode());
  Serial.print(F("Module ID        : ")); Serial.println(scale.getModuleID());
  Serial.print(F("I2C Address      : 0x")); Serial.println(scale.getI2CAddress(), HEX);
}

void testAdminUnlock() {
  Serial.println(F("\n--- 3. ADMIN UNLOCK TEST ---"));
  scale.unlockAdminMode(0x12345678);
  bool isAdmin = scale.isAdminMode();
  printResult(isAdmin, "Unlock Admin Mode", "Wrong password or communication error", String(isAdmin ? "Unlocked" : "Locked"));
}

void testEEPROM() {
  Serial.println(F("\n--- 4. EEPROM PARAMETER R/W TEST ---"));
  
  // Test Scale
  float oldScale = scale.getScale();
  scale.setScale(123.456);
  delay(50); // Wait for ForceSaveEeprom on PY32 to complete
  float newScale = scale.getScale();
  printResult(checkFloat(123.456, newScale), "Scale Float R/W", "EEPROM write/read mismatch", String(newScale, 3));
  scale.setScale(oldScale); // Restore
  delay(50);

  // Test Filter Level
  uint8_t oldFilter = scale.getFilterLevel();
  scale.setFilterLevel(3);
  delay(20);
  uint8_t newFilter = scale.getFilterLevel();
  printResult(newFilter == 3, "Filter Level R/W", "EEPROM write/read mismatch", String(newFilter));
  scale.setFilterLevel(oldFilter); // Restore
  delay(20);

  // Test Kalman
  float oldMea = scale.getKalmanMea();
  float oldEst = scale.getKalmanEst();
  float oldQ = scale.getKalmanQ();
  scale.setKalmanParameters(123.0, 123.0, 0.5);
  delay(20); // Chờ thêm 1 chút sau khi gửi bộ thông số cuối
  float newMea = scale.getKalmanMea();
  float newEst = scale.getKalmanEst();
  float newQ = scale.getKalmanQ();
  bool kalmanPass = checkFloat(123.0, newMea) && 
                    checkFloat(123.0, newEst) && 
                    checkFloat(0.5, newQ);
  String kalmanActual = String(newMea, 1) + "," + String(newEst, 1) + "," + String(newQ, 2);
  printResult(kalmanPass, "Kalman Params R/W", "EEPROM write/read mismatch", kalmanActual);
  scale.setKalmanParameters(oldMea, oldEst, oldQ); // Restore
  delay(20);
}

void testSensor() {
  Serial.println(F("\n--- 5. SENSOR ALIVE TEST ---"));
  int32_t raw = scale.getRawValue();
  float gram = scale.getGram();
  Serial.print(F("Raw Value: ")); Serial.println(raw);
  Serial.print(F("Gram Value: ")); Serial.println(gram);
  printResult(raw != 0 || gram != 0.0, "Sensor reading not stuck at 0", "Loadcell disconnected or damaged", "Raw=" + String(raw));
}

void testAdminLock() {
  Serial.println(F("\n--- 6. ADMIN LOCK TEST ---"));
  scale.lockAdminMode();
  bool isAdminLocked = scale.isAdminMode();
  printResult(!isAdminLocked, "Lock Admin Mode", "Failed to exit admin mode", String(isAdminLocked ? "Unlocked" : "Locked"));
}

void printFinalResult() {
  Serial.println(F("\n============================================="));
  if (errorCount == 0) {
    Serial.println(F("   FINAL RESULT: ALL TESTS PASSED [OK]"));
  } else {
    Serial.print(F("   FINAL RESULT: FAILED WITH "));
    Serial.print(errorCount);
    Serial.println(F(" ERRORS!"));
  }
  Serial.println(F("============================================="));
}

void testAll() {
  errorCount = 0; // Reset error count before running all tests
  testConnection();
  testInfo();
  testAdminUnlock();
  testEEPROM();
  testSensor();
  testAdminLock();
  printFinalResult();
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  while (!Serial);

  scale.begin(); // Initialize once so single tests can work properly

  printMenu();
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    switch(c) {
      case '1': testConnection(); break;
      case '2': testInfo(); break;
      case '3': testAdminUnlock(); break;
      case '4': testEEPROM(); break;
      case '5': testSensor(); break;
      case '6': testAdminLock(); break;
      case 'a':
      case 'A': testAll(); break;
      case '\n':
      case '\r': break;
      default:
        Serial.println(F("Unknown command."));
        printMenu();
        break;
    }
  }
}
