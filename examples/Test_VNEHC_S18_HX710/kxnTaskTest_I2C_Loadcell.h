#ifndef kxnTaskTest_I2C_Loadcell_H
#define kxnTaskTest_I2C_Loadcell_H

#include "kxnTask.h"
#include <Wire.h>
#include "MKE_I2C_Loadcell.h"
#include "Task_VNEHC_Test.h"

CREATE_TASK(kxnTaskTest_I2C_Loadcell)

MKE_I2C_Loadcell scale;
Stream *serial; // Đổi từ tham chiếu (&) sang con trỏ (*)
Task_VNEHC_Test * Task_VNEHC_Test1;

// Customize your reference weight (Unit: Grams)
float REFERENCE_WEIGHT_GRAM = 500.0;

void setup(float paReferenceWeightGram = 500.0, Task_VNEHC_Test *paTask_VNEHC_Test1 = NULL, Stream &paSerial = Serial)
{
    serial = &paSerial; // Lưu địa chỉ của Stream vào con trỏ
    Task_VNEHC_Test1 = paTask_VNEHC_Test1;
    kxnTaskManager.add(this);
    setState(0);
    kDelay(1000);

    Wire.begin();
    REFERENCE_WEIGHT_GRAM = paReferenceWeightGram;

    if (!scale.begin())
    {
        serial->println(F("I2C Loadcell not found. Please check connections!")); // Dùng -> thay vì .
        while (1)
            delay(100);
    }

    serial->println(F("I2C Loadcell connected successfully!"));
    serial->println(F("===================================="));
    serial->print(F("1. Scale Factor (Float): "));
    serial->println(scale.getScale(), 9);

    float currentScale = scale.getScale();
    uint32_t hexScale = *((uint32_t *)&currentScale);
    serial->print(F("2. Scale Factor (HEX)  : 0x"));
    serial->println(hexScale, HEX);
    serial->println(F("===================================="));

    serial->println(F("\n--- INSTRUCTIONS ---"));
    serial->println(F("1. Remove all items from the scale, send 't' to Tare (Zero)"));
    serial->print(F("2. Place the reference weight (e.g., "));
    serial->print(REFERENCE_WEIGHT_GRAM, 2);
    serial->println(F("g) on the scale, send 'c' to Calibrate"));
    serial->println(F("-----------------\n"));
}

void loop()
{
    // if (serial->available()) // Dùng -> thay vì .
    // {
    //     char cmd = serial->read();

    //     // TARE (ZERO)
    //     if (cmd == 't' || cmd == 'T')
    //     {
    //         serial->println(F("\n[CMD] Taring..."));
    //         scale.tare();
    //         serial->println(F("-> Tare successful. Weight reset to 0."));
    //     }

    //     // CALIBRATE
    //     else if (cmd == 'c' || cmd == 'C')
    //     {
    //         serial->print(F("\n[CMD] Calibrating with reference weight: "));
    //         serial->print(REFERENCE_WEIGHT_GRAM);
    //         serial->println(F("g ..."));

    //         scale.calibrate(REFERENCE_WEIGHT_GRAM);
    //         delay(500);

    //         serial->print(F("-> Calibration successful! New Scale Factor: "));
    //         serial->println(scale.getScale(), 6);
    //     }
    // }

    // Print weight continuously
    float weight = scale.getGram();
    if(isnan(weight)) {
        serial->println(F("Error reading weight!"));
        Task_VNEHC_Test1->OutPWR_off();
    } else {
        serial->print(F("Current Weight: "));
        serial->print(weight, 1);
        serial->println(F(" g"));
    }
    // serial->print(F("Current Weight: "));
    // serial->print(weight, 1);
    // serial->println(F(" g"));
}

void checkSerial(void * param = NULL)
{
    if (param == NULL || serial == NULL) return;

    String *cmdStr = (String *)param;
    String cmd = *cmdStr;

    // Xóa sạch khoảng trắng và ký tự ẩn (\r, \n) ở đầu/cuối chuỗi
    cmd.trim();

    // Dùng equalsIgnoreCase để bắt cả 't' lẫn 'T' bất kể định dạng xuống dòng
    if (cmd.equalsIgnoreCase("t"))
    {
        serial->println(F("\n[CMD] Taring..."));
        scale.tare();
        serial->println(F("-> Tare successful. Weight reset to 0."));
    }
    else if (cmd.equalsIgnoreCase("c"))
    {
        serial->print(F("\n[CMD] Calibrating with reference weight: "));
        serial->print(REFERENCE_WEIGHT_GRAM);
        serial->println(F("g ..."));

        scale.calibrate(REFERENCE_WEIGHT_GRAM);
        delay(550); // Đợi module lưu EEPROM

        serial->print(F("-> Calibration successful! New Scale Factor: "));
        serial->println(scale.getScale(), 6);
    }
}


END

#endif