/*
  Y260116: 
    - Kiem tra dien ap cua tin hieu 3V < S < 3V3 OK
    - Set ten theo chuan M0015_xxxx voi xxxx la 4 chu cuoi ma MAC
*/
#include "Task_VNEHC_Test.h"
#include "SoftwareSerial.h"
#include "MKE_M15.h"

Task_VNEHC_Test Task_VNEHC_Test1;

// #define PIN_PORT4_RX      A1
// #define PIN_PORT4_TX      A2
SoftwareSerial sSerial(PIN_PORT4_RX, PIN_PORT4_TX);


MKE_M15_SSerial(sSerial);

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
  // delay(1000);
  // Task_VNEHC_Test1.delayms(1000);
  if(Task_VNEHC_Test1.checkVolSignal4P_sSerial() != VNEHC_List_Error_None)
  {
    Task_VNEHC_Test1.OutPWR_off();
    Serial.println("\t\tSignal FAIL");
    Serial.println("\t1. ket noi day khong chac (TX - RX)");
    Serial.println("\t2. LDO 3V3 Loi");
    Serial.println("\t3. 5V-GND chap?");
    Serial.println("PLEASE RESET FOR NEXT TEST!");
    Serial.println("\t\tFAIL!");
    while(1);
  }
  else
  {
    Serial.println("\t\tSignal GOOD");
  }
  
  Task_VNEHC_Test1.delayms(100);
  

  Serial.println("PLEASE RESET FOR NEXT TEST!");
  Task_VNEHC_Test1.OutPWR_off();
}

// the loop routine runs over and over again forever:
void loop() {
  
}
