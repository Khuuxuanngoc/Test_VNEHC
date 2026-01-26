/*
    y260126:
      - KXN chương trình Đang build
    
      - Các bug thường gặp
        
    
        Phát hiện chập nguồn ngắt OK
        

*/


#include "Task_VNEHC_Test.h"

Task_VNEHC_Test Task_VNEHC_Test1;


#define VOLT_THESHOLD_UP_MIN      (6350)
#define VOLT_THESHOLD_UP_MAX      (6850)

#define VOLT_THESHOLD_DOWN_MIN      (0)
#define VOLT_THESHOLD_DOWN_MAX      (150)


// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        PIN_PORT3_SIG // On Trinket or Gemma, suggest changing this to 1

uint8_t flag_ShowPullUpErr = true;

void setup() {
  Serial.begin(115200);
  Task_VNEHC_Test1.setup();
  
  Task_VNEHC_Test1.checkVoltageCurrent();

  if(Task_VNEHC_Test1.checkCurrent_mA(50) != VNEHC_List_Error_None)
  {
    while(1);
  }

  // Task_VNEHC_Test1.checkVolSignal4P();
  if(Task_VNEHC_Test1.checkVolSignal3P() == VNEHC_List_Error_SIG_OVER_3V3)
  {
    // while(1)
    // {
    //   Serial.println("===");
    //   delay(2000);
    // }
  }

  Task_VNEHC_Test1.addHelp(help);

  showNote();
}

void loop() {
  checkAnalog2();
  
}

void checkAnalog2()
{
  if(Task_VNEHC_Test1.isPullUp_Port3_OK(0, VOLT_THESHOLD_UP_MIN, VOLT_THESHOLD_UP_MAX, 50) != VNEHC_List_Error_None)
  {
    if(flag_ShowPullUpErr == true)
    {
      flag_ShowPullUpErr = false;
      Serial.println(F("\t\tERROR PULLUP"));
      // Task_VNEHC_Test1.delayms(2000);  
    }
    
  }
  else
  {
    Serial.println(F("Dat sat mat sensor MKE0-S10 vao IR cua FLAME"));
    while(1)
    {
      if(Task_VNEHC_Test1.isPullDown_Port3_OK(0, VOLT_THESHOLD_DOWN_MIN, VOLT_THESHOLD_DOWN_MAX) == VNEHC_List_Error_None)
      {
        
        Task_VNEHC_Test1.delayms(100);
        
        if(Task_VNEHC_Test1.isPullUp_Port3_OK(0, VOLT_THESHOLD_UP_MIN, VOLT_THESHOLD_UP_MAX, 1000) == VNEHC_List_Error_None)
        {
          Serial.println(F("\t\tFLAME GOOD\t\t Sensor tiep theo"));
          flag_ShowPullUpErr = true;
          Task_VNEHC_Test1.delayms(100);
        }
        else
        {
          Serial.println(F("\t\tFLAME ERROR\t\t Sensor tiep theo"));
          flag_ShowPullUpErr = true;
          Task_VNEHC_Test1.delayms(1000);
        }

        break;
      }
      
    }
  }
}

void showNote()
{
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.println(F("LUU Y TRUOC KHI TEST"));
  Serial.println(F("su dung MKE-S10 Do line don dat sat vao Sensor nhat co the, sau do de Sensor trống"));
  Serial.println(F(""));
  Task_VNEHC_Test1.delayms(3000);
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