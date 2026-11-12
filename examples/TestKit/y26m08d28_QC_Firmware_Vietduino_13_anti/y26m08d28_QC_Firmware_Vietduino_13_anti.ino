/*
  Note:
   - 28/8/2026: y26m08d28_QC_Firmware_Vietduino_12
     - Add board VNEHC bluepill
     - Edit: 
       - Replace my_pin_array[11].pin with KXN_LED_DEFAULT

   - y21m10d15: 
     + Add variable_board.h
     + Test OK Leonardo, Mega2560, Uno
     
   - 19/6/2021 Test OK Board Micro, Mega2560 Pro embed, Mega2560 WiFi, Uno WiFi
   - 17/11/2019: Không code trong void setup và loop nữa, toàn bộ chuyển qua CREATE_FUNCTION
   https://arduino.stackexchange.com/questions/21137/arduino-how-to-get-the-board-type-in-code
   
   - 26/2/2019: thêm vị trí chân Mega bị lỗi VD: 3.6 là chân số 89 (Mega chia làm 4 mặt, chân 1 được tính ở mặt một, số thập phân là vị trí mặt đó) => mặt 4, ở giữa.

   - 28/10/2022 Add VietESP32 - Wroom
   - 9/4/2023 1 chan GND, kiem tra trang thai cac chan con lai
   - 24/5/2023 V8: Add wifi scan cho ESP8266 và ESP32
   - 26/5/2023 V9: ESP32 check them pin 0-21-22
   - 21/11/2025 V10: Thêm Vietduino ESP32-S3-Wroom-1
   - 5/1/2026 V11: Thêm ESP32-S3-Devkit-N16R8 có WS2812B
   - 12/11/2026 V13 (Optimized & Fixed):
     + Vá lỗi tràn bộ nhớ kxnSprintf và showAnalogValue
     + Giữ nguyên giải thuật testChap_setup_2 đồng bộ nhanh 1-pass (không yield giữa chừng gây hỏng stack)
     + Sửa tính toán vị trí chân chip Mega posOnChip
     + Tương thích ngược 100% với các thông báo chuẩn của Vietduino
*/

#include "Vietduino_NewFunction.h"
#include "variable_board.h"

#define DBL(x)      Serial.println(x)

#define ID_STORE    "2.0"

#if defined(ID_KXN)
  #define QC_ID ID_KXN
#elif defined(ID_STORE)
  #define QC_ID ID_STORE
#elif defined(ID_ONLINE)
  #define QC_ID ID_ONLINE
#else
  #define QC_ID "2.0"
#endif

// Bộ đệm an toàn cho kxnSprintf
static char s_formatBuffer[96];
#define kxnSprintf(...) do { \
    snprintf(s_formatBuffer, sizeof(s_formatBuffer), __VA_ARGS__); \
    Serial.print(s_formatBuffer); \
} while(0)

int ledpin = KXN_LED_DEFAULT;
int Start_pin = 0;
int Stop_pin = 18;
int start_pin_Analog = 14;

unsigned char default_pin_value = LOW;
bool b_complete_bit = false;
bool b_tested_low_bit = false;

#if NUM_DIGITAL_PINS_2 > 68 // Mega có 70 chân
byte viTriLoi[70]{
  //             0          1         2         3         4         5         6         7         8         9
                 2,         3,        6,        7,        1,        5,        15,       16,       17,       18,  //     0
                 23,        24,       25,       26,       64,       63,       13,       12,       46,       45,  //     1
                 44,        43,       78,       77,       76,       75,       74,       73,       72,       71,  //     2
                 60,        59,       58,       57,       56,       55,       54,       53,       50,       70,  //     3
                 52,        51,       42,       41,       40,       39,       38,       37,       36,       35,  //     4
                 22,        21,       20,       19,       97,       96,       95,       94,       93,       92,  //     5
                 91,        90,       89,       88,       87,       86,       85,       84,       83,       82   //     6
};

String ErrcodeToStr(int _errCode_){
  uint8_t pinPos = my_pin_array[_errCode_].posOnChip;
  if (pinPos == 0 && _errCode_ < 70) {
    pinPos = viTriLoi[_errCode_];
  }
  float side = (float)pinPos / 25.0f;
  return String(side, 1) + " (ChipPin: " + String(pinPos) + ")";
}
#endif

// Khai báo trước các hàm phụ trợ
void ShowAnalogPin_Error(uint32_t cf);
void CheckAllPinState(int pa_SamplePin, int sampleIndex = -1);
void resetErrorAllPin();
void showAnalogValue(int *tempArray_ValuePinAnalog, int tempCountPinAnalog);

void setAllPinPullUp(){
  for(int cf = Start_pin; cf <= Stop_pin; cf++){
    pinMode(my_pin_array[cf].pin, INPUT_PULLUP);
    my_pin_array[cf].lastValue = HIGH;
  }
}

void ShowAnalogPin_Error(uint32_t cf){  
  if(my_pin_array[cf].type == _PIN_TYPE_A_){
    #if defined(ARDUINO_ARCH_ESP32)
      Serial.print(F("GPIO"));
      Serial.print(my_pin_array[cf].pin);
    #elif defined(ARDUINO_ARCH_STM32)
      Serial.print(my_pin_array[cf].name);
    #else
      Serial.print(F("A"));
      Serial.print(my_pin_array[cf].pin - A0);
    #endif
  } else {
    Serial.print(my_pin_array[cf].name);
  }
}

CREATE_FUNCTION(ShowPinState){
  static int cf;
  cf = 0;
  Serial.println(F("==========="));
  for(cf = Start_pin; cf <= Stop_pin; cf++){
      if(my_pin_array[cf].lastValue == !default_pin_value){
        continue;
      }else{
        if(my_pin_array[cf].lastValue == default_pin_value){
          Serial.print(F("Pin "));
          Serial.print(default_pin_value ? F("HIGH: ") : F("LOW: "));
          ShowAnalogPin_Error(cf);
          
          #if NUM_DIGITAL_PINS_2 > 68 // Mega có 70 chân
            Serial.print(F("\t"));
            Serial.print(ErrcodeToStr(cf));
          #endif
          
          Serial.println();
          M_DELAY(0);
        }
      }
  }
  M_DELAY(1000);
  ShowPinState.disable();
  END_CREATE_FUNCTION
}

CREATE_FUNCTION(blink_led_ok){
  #if defined(ARDUINO_ARCH_ESP32)
    ledpin = KXN_LED_DEFAULT;
    ESP32_scanWiFi_init();
    blink_led_ok.disable();
  #elif defined(ARDUINO_ARCH_ESP8266)
    ESP8266_BlinkScanWiFi();
  #else
    #ifndef KT_TEST
    pinMode(KXN_LED_DEFAULT, OUTPUT);
    #endif

    while(1){
      static int tempState = 1;
      #ifndef KT_TEST
        if(!b_tested_low_bit) {
          digitalWrite(KXN_LED_DEFAULT, tempState ? KXN_LED_ACTIVE_DEFAULT : !KXN_LED_ACTIVE_DEFAULT);
        } else {
          Serial.println(F("Vietduino Test wire done, all pins are OK!"));
        }
      #endif

      if(tempState == 1){
        Serial.println(F("Hshop tests Arduino lan 3 OK!!"));
      }
      tempState = !tempState;
      M_DELAY(100);
    }
  #endif
  END_CREATE_FUNCTION
}

#pragma region CREATE_FUNCTION(TestLow)
/*
  @ Kịch bản: Khi các chân đều LOW thì chương trình kết thúc. Nếu còn bất kỳ chân IO nào đang ở mức HIGH, chương trình sẽ show ra Serial các IO đó.
*/
CREATE_FUNCTION(TestLow){
  Serial.println(F("Test I/O Low begin:"));
  default_pin_value = HIGH;
  
  blink_led_ok.disable();
  setAllPinPullUp();
  M_DELAY(100);
  b_complete_bit = false;
  
  while(!b_complete_bit){
    M_DELAY(0);
    
    static int cf;
    cf = 0;
    static bool flag_check_again = false;
    flag_check_again = false;
    
    for(cf = Start_pin; cf <= Stop_pin; cf++){
      if(my_pin_array[cf].lastValue == !default_pin_value){
        continue;
      }else{
        int temValPin = digitalRead(my_pin_array[cf].pin);
        b_complete_bit = true;
        if(temValPin == default_pin_value){
          flag_check_again = true;
        }else if(temValPin == !default_pin_value){
          my_pin_array[cf].lastValue = !default_pin_value;
        }
      }
    }
    if(flag_check_again){
      b_complete_bit = false;
    }
    
    if(!ShowPinState.available()) ShowPinState.enable();
  }

  if(b_complete_bit)
    Serial.println(F("Vietduino Test wire done, all pins are OK!"));
  
  TestLow.disable();
  b_tested_low_bit = true;
  blink_led_ok.enable();
  END_CREATE_FUNCTION
}
#pragma endregion CREATE_FUNCTION(TestLow)

void ShowPinArr(){
  Serial.print(F("Stoppin: "));
  Serial.println(Stop_pin);

  for(int cf = 0; cf <= Stop_pin; cf++){
    Serial.print(my_pin_array[cf].lastValue); Serial.print(F(", "));
    Serial.print(my_pin_array[cf].pin);       Serial.print(F(", "));
    Serial.print(my_pin_array[cf].type);      Serial.println();
  }
  Serial.println(F("done!"));
}

void setup() {
  Serial.begin(9600);
  Stop_pin = sizeArray - 1;
  
  setAllPinPullUp();

  uint8_t temCount = 0;
  while(!Serial){
    delay(1000);
    temCount++;
    if(temCount == 2) break;
  }
  
  if(String(BOARD) == "Micro"){
    Stop_pin = STOP_PIN_DEFAULT_MICRO;
  }

  TestLow.disable();
  ShowPinState.disable();
  blink_led_ok.disable();

  Serial.println("There are " + String(sizeArray) + " pin need check");
  Serial.println(F("Welcome to Vietduino, test begin!"));
  Serial.println("Version firmWare test: " + String(BOARD));
  Serial.println(F("Author: Mr.Ngoc - 0938 022 500"));
}

void loop() {
  VIETDUINO_UPDATE;
}

#pragma region testChap funtion
CREATE_FUNCTION(testChap_setup_2){
  setAllPinPullUp();
  resetErrorAllPin();
  b_complete_bit = false;

  for(int cf = Start_pin; cf <= Stop_pin; cf++){
    if(my_pin_array[cf].mode == MODE_PIN_I){
      continue;
    }else{
      int tempValue = digitalRead(my_pin_array[cf].pin);
      if(tempValue == 0){
        Serial.print(F("Warning: pin "));
        ShowAnalogPin_Error(cf);
        Serial.println(F(" CAN NOT Pullup"));
        b_complete_bit = true;
      }

      pinMode(my_pin_array[cf].pin, OUTPUT);
      digitalWrite(my_pin_array[cf].pin, 0);

      CheckAllPinState(my_pin_array[cf].pin, cf);
      
      setAllPinPullUp();
    }
  }
  
  for(int cf = Start_pin; cf <= Stop_pin; cf++){
    pinMode(my_pin_array[cf].pin, INPUT);
    my_pin_array[cf].lastValue = HIGH;
  }

  if(!b_complete_bit){
    Serial.println(F("Congratulation, Vietduino is working very good!"));
    blink_led_ok.enable();
  }else{
    Serial.println(F("Some pin has proplem please check hardware again!"));
  }
  testChap_setup_2.disable();
  END_CREATE_FUNCTION
}
#pragma endregion testChap funtion

CREATE_FUNCTION(CheckSeria_command){
  if(Serial.available()){
    char kk = Serial.read();
    
    if(kk == '0') {
      testChap_setup_2.enable();
    }else{
      if(b_complete_bit){
        if(!TestLow.available() && (!b_tested_low_bit)){
          TestLow.enable();
        }
      }
    } 
  }
  END_CREATE_FUNCTION
}

void testOnlyAnalogPin(){
  int tempCountPinAnalog = 0;
  for(int cf = 0; cf <= Stop_pin; cf++){
    if(my_pin_array[cf].name[0] == 'A'){
      tempCountPinAnalog++;
    }
  }

  if (tempCountPinAnalog == 0) {
    Serial.println(F("No analog pins on this board!"));
    return;
  }

  int tempArray_ValuePinAnalog[tempCountPinAnalog];

  Serial.print(tempCountPinAnalog);
  Serial.println(F(" pin analog:"));
  setAllPinPullUp();
  while(1){
    showAnalogValue(tempArray_ValuePinAnalog, tempCountPinAnalog);
    delay(100);
    #if defined(ESP8266) || defined(ARDUINO_ARCH_ESP8266)
    yield();
    #endif
  }
}

void resetErrorAllPin(){
  for(int cf = Start_pin; cf <= Stop_pin; cf++){
    my_pin_array[cf].lastError = false;
  }
}

void CheckAllPinState(int pa_SamplePin, int sampleIndex){
  int tempValue_After = 1;

  for(int cf = Start_pin; cf <= Stop_pin; cf++){
    if(my_pin_array[cf].mode == MODE_PIN_I){
      continue;
    }

    if(my_pin_array[cf].pin == pa_SamplePin){
      continue;
    }

    if(my_pin_array[cf].mode == MODE_PIN_IA){
      tempValue_After = 0;
      for(int cf1 = 0; cf1 < 10; cf1++){
        tempValue_After += analogRead(my_pin_array[cf].pin);
      }
      tempValue_After = tempValue_After / 10;
      if (tempValue_After < 50) tempValue_After = 0;
      else tempValue_After = 1;
    }else{
      tempValue_After = digitalRead(my_pin_array[cf].pin);
    }

    if(tempValue_After == 0){
      pinMode(my_pin_array[cf].pin, INPUT_PULLUP);
      if(!my_pin_array[cf].lastError){
        my_pin_array[cf].lastError = true;
        Serial.print(F("May be pin "));
        ShowAnalogPin_Error(cf);

        Serial.print(F(" error"));
        if (sampleIndex >= 0) {
          Serial.print(F(" (short with "));
          ShowAnalogPin_Error(sampleIndex);
          Serial.print(F(")"));
        }

        #if NUM_DIGITAL_PINS_2 > 68 // Mega có 70 chân
          Serial.print(F("\t"));
          Serial.print(ErrcodeToStr(cf));
        #endif

        Serial.println();
      }
      b_complete_bit = true;
    }
  }
}

void showAnalogValue(int *tempArray_ValuePinAnalog, int tempCountPinAnalog){
  int tempCount = 0;
  for(int cf3 = 0; cf3 <= Stop_pin; cf3++){
    if(my_pin_array[cf3].name[0] == 'A'){
      if(tempCount < tempCountPinAnalog){
        tempArray_ValuePinAnalog[tempCount] = analogRead(my_pin_array[cf3].pin);
        tempCount++;
      }
    }
  }
  for(int cf3 = 0; cf3 < tempCountPinAnalog; cf3++){
    Serial.print(tempArray_ValuePinAnalog[cf3]);
    Serial.print('\t');
  }
  Serial.println();
}
