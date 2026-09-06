/*
  Y260901:
  Code test MKE HX710 OK: Kiem tra dien ap cua tin hieu 3V < S < 3V3 OK
  Y260116: 
    - Kiem tra dien ap cua tin hieu 3V < S < 3V3 OK
    - Set ten theo chuan M0015_xxxx voi xxxx la 4 chu cuoi ma MAC
*/
#include "Task_VNEHC_Test.h"
#include "SoftwareSerial.h"
#include "MKE_M15.h"
#include "kxnTaskTest_I2C_Loadcell.h"

Task_VNEHC_Test Task_VNEHC_Test1;

// #define PIN_PORT4_RX      A1
// #define PIN_PORT4_TX      A2
// SoftwareSerial sSerial(PIN_PORT4_RX, PIN_PORT4_TX);


// MKE_M15_SSerial(sSerial);
kxnTaskTest_I2C_Loadcell kxnTaskTest_I2C_Loadcell1;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  // delay(1000);

  Task_VNEHC_Test1.VNEHC_Serial = &Serial;
  
  Task_VNEHC_Test1.OutPWR_setup();
  
  
  if(Task_VNEHC_Test1.setup() != VNEHC_List_Error_None)
  {
    Serial.println(F("VNEHC Test: Setup Error!"));
    while(1);
  }

  Task_VNEHC_Test1.addCMD(wrapperLoadcellCMD);
  
  Task_VNEHC_Test1.delayms(100);

  Serial.println(F("START TEST I2C LOAD CELL! checkVoltageCurrent()"));

  if(Task_VNEHC_Test1.checkCurrent_mA(20) != VNEHC_List_Error_None)
  {
    // while(1);
  }

  Serial.println(F("START TEST I2C LOAD CELL!"));
  // Task_VNEHC_Test1.OutPWR_off();

  kxnTaskTest_I2C_Loadcell1.setup(200.0, &Task_VNEHC_Test1);
}

// the loop routine runs over and over again forever:
void loop() {
  // // read the input on analog pin 0:
  

  // // checkSerial(&Serial, &Serial);
  // autoSendAT();
  kxnTaskManager.run(millis());
}


void help()
{
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(F("Kiem tra ho chan R ke ben Lable SENSOR"));
  Serial.println(F("Kiem tra LDO 3V3"));
  Serial.println(F(""));
  Task_VNEHC_Test1.delayms(3000);
}

// 1. Định nghĩa hàm trung gian toàn cục
void wrapperLoadcellCMD(void *param) {
    // Gọi trực tiếp method từ instance cụ thể của bạn
    kxnTaskTest_I2C_Loadcell1.checkSerial(param); 
}