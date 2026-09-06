#include <Wire.h>
#include "MKE_I2C_Loadcell.h"

MKE_I2C_Loadcell scale;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  if (!scale.begin()) {
    Serial.println("Khong tim thay Loadcell I2C. Hay kiem tra ket noi!");
    while (1) delay(100);
  }
  
  Serial.println("Ket noi Loadcell I2C thanh cong!");
  Serial.print("He so scale hien tai tu EEPROM: ");
  Serial.println(scale.getScale(), 6);

  Serial.println("\n=== HUONG DAN ===");
  Serial.println("Go 't' roi nhan Enter de TARE (Tru bi)");
  Serial.println("Go 'c' roi nhan Enter de CALIBRATE (Hieu chuan 100g)");
  Serial.println("=================\n");
}

void loop() {
  // Xử lý lệnh từ Serial Monitor
  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 't' || cmd == 'T') {
      Serial.println("\n[LENH] Dang tru bi (Tare)...");
      scale.tare();
    } 
    else if (cmd == 'c' || cmd == 'C') {
      Serial.println("\n[LENH] Dang hieu chuan voi qua can 100g...");
      scale.calibrate(100.0);
      delay(500);
      Serial.print("-> He so scale moi luu vao EEPROM: ");
      Serial.println(scale.getScale(), 6);
    }
  }

  // Đọc và in giá trị
  float weight = scale.getGram();
  float carat = scale.getCarat();
  
  Serial.print("Khoi luong: ");
  Serial.print(weight, 2);
  Serial.print(" g | ");
  
  Serial.print(carat, 2);
  Serial.println(" ct");
  
  delay(500);
}
