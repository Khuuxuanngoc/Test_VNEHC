#include "variable_board.h"

#if defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_ADK) || defined(HSHOP_TEST_BOARD_MEGA2560_PRO_EMBED_BLACK) || defined(HSHOP_TEST_BOARD_MEGA2560_WIFI_BLACK)
//       pin_info my_pin_array[] = {
//       //LastValue,  pin,    Type
//             {1,            2,            _PIN_TYPE_D_},
//             {2,            3,            _PIN_TYPE_D_},
//             {3,            4,            _PIN_TYPE_D_},
//             {4,            5,            _PIN_TYPE_D_},
//             {5,            6,            _PIN_TYPE_D_},
//             {6,            7,            _PIN_TYPE_D_},
//             {7,            8,            _PIN_TYPE_D_},
//             {8,            9,            _PIN_TYPE_D_},
//             {9,            10,            _PIN_TYPE_D_},
//             {10,            11,            _PIN_TYPE_D_},
//             {11,            12,            _PIN_TYPE_D_},
//             {12,            13,            _PIN_TYPE_D_},
//             {13,            14,            _PIN_TYPE_D_},
//             {14,            15,            _PIN_TYPE_D_},
//             {15,            16,            _PIN_TYPE_D_},
//             {16,            17,            _PIN_TYPE_D_},
//             {17,            18,            _PIN_TYPE_D_},
//             {18,            19,            _PIN_TYPE_D_},
//             {19,            20,            _PIN_TYPE_D_},
//             {20,            21,            _PIN_TYPE_D_},
//             {21,            22,            _PIN_TYPE_D_},
//             {22,            23,            _PIN_TYPE_D_},
//             {23,            24,            _PIN_TYPE_D_},
//             {24,            25,            _PIN_TYPE_D_},
//             {25,            26,            _PIN_TYPE_D_},
//             {26,            27,            _PIN_TYPE_D_},
//             {27,            28,            _PIN_TYPE_D_},
//             {28,            29,            _PIN_TYPE_D_},
//             {29,            30,            _PIN_TYPE_D_},
//             {30,            31,            _PIN_TYPE_D_},
//             {31,            32,            _PIN_TYPE_D_},
//             {32,            33,            _PIN_TYPE_D_},
//             {33,            34,            _PIN_TYPE_D_},
//             {34,            35,            _PIN_TYPE_D_},
//             {35,            36,            _PIN_TYPE_D_},
//             {36,            37,            _PIN_TYPE_D_},
//             {37,            38,            _PIN_TYPE_D_},
//             {38,            39,            _PIN_TYPE_D_},
//             {39,            40,            _PIN_TYPE_D_},
//             {40,            41,            _PIN_TYPE_D_},
//             {41,            42,            _PIN_TYPE_D_},
//             {42,            43,            _PIN_TYPE_D_},
//             {43,            44,            _PIN_TYPE_D_},
//             {44,            45,            _PIN_TYPE_D_},
//             {45,            46,            _PIN_TYPE_D_},
//             {46,            47,            _PIN_TYPE_D_},
//             {47,            48,            _PIN_TYPE_D_},
//             {48,            49,            _PIN_TYPE_D_},
//             {49,            50,            _PIN_TYPE_D_},
//             {50,            51,            _PIN_TYPE_D_},
//             {51,            52,            _PIN_TYPE_D_},
//             {52,            53,            _PIN_TYPE_D_},
//             {53,            A0,            _PIN_TYPE_A_},
//             {54,            A1,            _PIN_TYPE_A_},
//             {55,            A2,            _PIN_TYPE_A_},
//             {56,            A3,            _PIN_TYPE_A_},
//             {57,            A4,            _PIN_TYPE_A_},
//             {58,            A5,            _PIN_TYPE_A_},
//             {59,            A6,            _PIN_TYPE_A_},
//             {60,            A7,            _PIN_TYPE_A_},
//             {61,            A8,            _PIN_TYPE_A_},
//             {62,            A9,            _PIN_TYPE_A_},
//             {63,            A10,            _PIN_TYPE_A_},
//             {64,            A11,            _PIN_TYPE_A_},
//             {65,            A12,            _PIN_TYPE_A_},
//             {66,            A13,            _PIN_TYPE_A_},
//             {67,            A14,            _PIN_TYPE_A_},
//             {68,            A15,            _PIN_TYPE_A_}
// };
      pin_info my_pin_array[] = {
            // {LastValue,      pin,                    type,                  mode,              posOnchip,       name},
            {1,               2,                _PIN_TYPE_D_,           MODE_PIN_IO,               6,           "D2"},
            {2,               3,                _PIN_TYPE_D_,           MODE_PIN_IO,               7,           "D3"},
            {3,               4,                _PIN_TYPE_D_,           MODE_PIN_IO,               1,           "D4"},
            {4,               5,                _PIN_TYPE_D_,           MODE_PIN_IO,               5,           "D5"},
            {5,               6,                _PIN_TYPE_D_,           MODE_PIN_IO,               15,          "D6"},
            {6,               7,                _PIN_TYPE_D_,           MODE_PIN_IO,               16,          "D7"},
            {7,               8,                _PIN_TYPE_D_,           MODE_PIN_IO,               17,          "D8"},
            {8,               9,                _PIN_TYPE_D_,           MODE_PIN_IO,               18,          "D9"},
            {9,               10,               _PIN_TYPE_D_,           MODE_PIN_IO,               23,          "D10"},
            {10,              11,               _PIN_TYPE_D_,           MODE_PIN_IO,               24,           "D11"},
            {11,              12,               _PIN_TYPE_D_,           MODE_PIN_IO,               25,           "D12"},
            {12,              13,               _PIN_TYPE_D_,           MODE_PIN_IO,               26,           "D13"},
            {13,              14,               _PIN_TYPE_D_,           MODE_PIN_IO,               64,           "D14"},
            {14,              15,               _PIN_TYPE_D_,           MODE_PIN_IO,               63,           "D15"},
            {15,              16,               _PIN_TYPE_D_,           MODE_PIN_IO,               13,           "D16"},
            {16,              17,               _PIN_TYPE_D_,           MODE_PIN_IO,               12,           "D17"},
            {17,              18,               _PIN_TYPE_D_,           MODE_PIN_IO,               46,           "D18"},
            {18,              19,               _PIN_TYPE_D_,           MODE_PIN_IO,               45,           "D19"},
            {19,              20,               _PIN_TYPE_D_,           MODE_PIN_IO,               44,           "D20"},
            {20,              21,               _PIN_TYPE_D_,           MODE_PIN_IO,               43,           "D21"},
            {21,              22,               _PIN_TYPE_D_,           MODE_PIN_IO,               78,           "D22"},
            {22,              23,               _PIN_TYPE_D_,           MODE_PIN_IO,               77,           "D23"},
            {23,              24,               _PIN_TYPE_D_,           MODE_PIN_IO,               76,           "D24"},
            {24,              25,               _PIN_TYPE_D_,           MODE_PIN_IO,               75,           "D25"},
            {25,              26,               _PIN_TYPE_D_,           MODE_PIN_IO,               74,           "D26"},
            {26,              27,               _PIN_TYPE_D_,           MODE_PIN_IO,               73,           "D27"},
            {27,              28,               _PIN_TYPE_D_,           MODE_PIN_IO,               72,           "D28"},
            {28,              29,               _PIN_TYPE_D_,           MODE_PIN_IO,               71,           "D29"},
            {29,              30,               _PIN_TYPE_D_,           MODE_PIN_IO,               60,           "D30"},
            {30,              31,               _PIN_TYPE_D_,           MODE_PIN_IO,               59,           "D31"},
            {31,              32,               _PIN_TYPE_D_,           MODE_PIN_IO,               58,           "D32"},
            {32,              33,               _PIN_TYPE_D_,           MODE_PIN_IO,               57,           "D33"},
            {33,              34,               _PIN_TYPE_D_,           MODE_PIN_IO,               56,           "D34"},
            {34,              35,               _PIN_TYPE_D_,           MODE_PIN_IO,               55,           "D35"},
            {35,              36,               _PIN_TYPE_D_,           MODE_PIN_IO,               54,           "D36"},
            {36,              37,               _PIN_TYPE_D_,           MODE_PIN_IO,               53,           "D37"},
            {37,              38,               _PIN_TYPE_D_,           MODE_PIN_IO,               50,           "D38"},
            {38,              39,               _PIN_TYPE_D_,           MODE_PIN_IO,               70,           "D39"},
            {39,              40,               _PIN_TYPE_D_,           MODE_PIN_IO,               52,           "D40"},
            {40,              41,               _PIN_TYPE_D_,           MODE_PIN_IO,               51,           "D41"},
            {41,              42,               _PIN_TYPE_D_,           MODE_PIN_IO,               42,           "D42"},
            {42,              43,               _PIN_TYPE_D_,           MODE_PIN_IO,               41,           "D43"},
            {43,              44,               _PIN_TYPE_D_,           MODE_PIN_IO,               40,           "D44"},
            {44,              45,               _PIN_TYPE_D_,           MODE_PIN_IO,               39,           "D45"},
            {45,              46,               _PIN_TYPE_D_,           MODE_PIN_IO,               38,           "D46"},
            {46,              47,               _PIN_TYPE_D_,           MODE_PIN_IO,               37,           "D47"},
            {47,              48,               _PIN_TYPE_D_,           MODE_PIN_IO,               36,           "D48"},
            {48,              49,               _PIN_TYPE_D_,           MODE_PIN_IO,               35,           "D49"},
            {49,              50,               _PIN_TYPE_D_,           MODE_PIN_IO,               22,           "D50"},
            {50,              51,               _PIN_TYPE_D_,           MODE_PIN_IO,               21,           "D51"},
            {51,              52,               _PIN_TYPE_D_,           MODE_PIN_IO,               20,           "D52"},
            {52,              53,               _PIN_TYPE_D_,           MODE_PIN_IO,               19,           "D53"},
            {53,              A0,               _PIN_TYPE_A_,           MODE_PIN_IO,               97,           "A0"},
            {54,              A1,               _PIN_TYPE_A_,           MODE_PIN_IO,               96,           "A1"},
            {55,              A2,               _PIN_TYPE_A_,           MODE_PIN_IO,               95,           "A2"},
            {56,              A3,               _PIN_TYPE_A_,           MODE_PIN_IO,               94,           "A3"},
            {57,              A4,               _PIN_TYPE_A_,           MODE_PIN_IO,               93,           "A4"},
            {58,              A5,               _PIN_TYPE_A_,           MODE_PIN_IO,               92,           "A5"},
            {59,              A6,               _PIN_TYPE_A_,           MODE_PIN_IO,               91,           "A6"},
            {60,              A7,               _PIN_TYPE_A_,           MODE_PIN_IO,               90,           "A7"},
            {61,              A8,               _PIN_TYPE_A_,           MODE_PIN_IO,               89,           "A8"},
            {62,              A9,               _PIN_TYPE_A_,           MODE_PIN_IO,               88,           "A9"},
            {63,              A10,              _PIN_TYPE_A_,           MODE_PIN_IO,               87,           "A10"},
            {64,              A11,              _PIN_TYPE_A_,           MODE_PIN_IO,               86,           "A11"},
            {65,              A12,              _PIN_TYPE_A_,           MODE_PIN_IO,               85,           "A12"},
            {66,              A13,              _PIN_TYPE_A_,           MODE_PIN_IO,               84,           "A13"},
            {67,              A14,              _PIN_TYPE_A_,           MODE_PIN_IO,               83,           "A14"},
            {68,              A15,              _PIN_TYPE_A_,           MODE_PIN_IO,               82,           "A15"},
      };


#elif defined(ARDUINO_AVR_LEONARDO) || defined(ARDUINO_AVR_NANO) || defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_PRO) || defined(HSHOP_TEST_BOARD_UNO_WIFI_BLACK) || defined(ARDUINO_AVR_MICRO)       

      pin_info my_pin_array[] = {
      // //LastValue,  pin,    Type
      //       {1,       2,      _PIN_TYPE_D_, MODE_PIN_IO},
      //       {2,       3,      _PIN_TYPE_D_, MODE_PIN_IO},
      //       {3,       4,      _PIN_TYPE_D_, MODE_PIN_IO},
      //       {4,       5,      _PIN_TYPE_D_, MODE_PIN_IO},
      //       {5,       6,      _PIN_TYPE_D_, MODE_PIN_IO},
      //       {6,       7,      _PIN_TYPE_D_, MODE_PIN_IO},
      //       {7,       8,      _PIN_TYPE_D_, MODE_PIN_IO},
      //       {8,       9,      _PIN_TYPE_D_, MODE_PIN_IO},
      //       {9,       10,     _PIN_TYPE_D_, MODE_PIN_IO},
      //       {10,       11,     _PIN_TYPE_D_, MODE_PIN_IO},
      //       {11,       12,     _PIN_TYPE_D_, MODE_PIN_IO},
      //       {12,       13,     _PIN_TYPE_D_, MODE_PIN_I},

      //       {13,       A0,     _PIN_TYPE_A_, MODE_PIN_IO},
      //       {14,       A1,     _PIN_TYPE_A_, MODE_PIN_IO},
      //       {15,       A2,     _PIN_TYPE_A_, MODE_PIN_IO},
      //       {16,       A3,     _PIN_TYPE_A_, MODE_PIN_IO},
      //       {17,       A4,     _PIN_TYPE_A_, MODE_PIN_IO},
      //       {18,       A5,     _PIN_TYPE_A_, MODE_PIN_IO}

            // {LastValue,      pin,                    type,           mode,      posOnchip,      name},
            {1,               2,                _PIN_TYPE_D_,       MODE_PIN_IO,     0,         "D2"},
            {2,               3,                _PIN_TYPE_D_,       MODE_PIN_IO,     0,         "D3"},
            {3,               4,                _PIN_TYPE_D_,       MODE_PIN_IO,     0,         "D4"},
            {4,               5,                _PIN_TYPE_D_,       MODE_PIN_IO,     0,         "D5"},
            {5,               6,                _PIN_TYPE_D_,       MODE_PIN_IO,     0,         "D6"},
            {6,               7,                _PIN_TYPE_D_,       MODE_PIN_IO,     0,         "D7"},
            {7,               8,                _PIN_TYPE_D_,       MODE_PIN_IO,     0,         "D8"},
            {8,               9,                _PIN_TYPE_D_,       MODE_PIN_IO,     0,         "D9"},
            {9,               10,               _PIN_TYPE_D_,       MODE_PIN_IO,      0,        "D10"},
            {10,              11,               _PIN_TYPE_D_,       MODE_PIN_IO,      0,        "D11"},
            {11,              12,               _PIN_TYPE_D_,       MODE_PIN_IO,      0,        "D12"},
            {12,              13,               _PIN_TYPE_D_,       MODE_PIN_IO,      0,        "D13"},
            {13,              A0,               _PIN_TYPE_A_,       MODE_PIN_IO,      0,        "A0"},
            {14,              A1,               _PIN_TYPE_A_,       MODE_PIN_IO,      0,        "A1"},
            {15,              A2,               _PIN_TYPE_A_,       MODE_PIN_IO,      0,        "A2"},
            {16,              A3,               _PIN_TYPE_A_,       MODE_PIN_IO,      0,        "A3"},
            {17,              A4,               _PIN_TYPE_A_,       MODE_PIN_IO,      0,        "A4"},
            {18,              A5,               _PIN_TYPE_A_,       MODE_PIN_IO,      0,        "A5"}

      };

#elif defined(ARDUINO_ARCH_ESP32)
      #include "WiFi.h" // V2.0.9

      TaskHandle_t Task1;
      TaskHandle_t Task2;
      int numOfWifi = 0;
      unsigned long ledDelay = 100;
      
      
      #if defined(ESP32S3_N16R8_DEVKIT) 
            #include <Adafruit_NeoPixel.h>
            // Which pin on the Arduino is connected to the NeoPixels?
            #define PIN        KXN_LED_DEFAULT // On Trinket or Gemma, suggest changing this to 1

            // How many NeoPixels are attached to the Arduino?
            #define NUMPIXELS 1 // Popular NeoPixel ring size
            // Adafruit_NeoPixel *pPixels;
            Adafruit_NeoPixel Pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

            #define KXN_ON_LED(x)         Pixels.setPixelColor(0, Pixels.Color(255, 255, 255)); \
                                          Pixels.show();  \
                                          delay(x);

            #define KXN_OFF_LED(x)        Pixels.clear(); \
                                          Pixels.show();  \
                                          delay(x);

            #define KXN_CONTROL_LED(x)          KXN_ON_LED(x) \
                                                KXN_OFF_LED(x)

            void Task1code( void * pvParameters ){
                  Serial.print("Task1 running on core ");
                  Serial.println(xPortGetCoreID());
                  
                  Pixels.begin();

                  for(;;){
                        if((numOfWifi > 0) && (numOfWifi < 3)){
                              KXN_CONTROL_LED(1000)
                              KXN_CONTROL_LED(1000)
                        }else if(numOfWifi <= 0){
                              KXN_OFF_LED(2000)
                        }else{
                              for(int cff = 0; cff <10; cff++){
                                    KXN_CONTROL_LED(100)
                              }
                        }
                  } 
            }
      #else
            void Task1code( void * pvParameters ){
                  Serial.print("Task1 running on core ");
                  Serial.println(xPortGetCoreID());
                  pinMode(KXN_LED_DEFAULT, OUTPUT);
                  for(;;){
                        // digitalWrite(ledpin, HIGH);
                        // delay(ledDelay);
                        // digitalWrite(ledpin, LOW);
                        // delay(ledDelay);

                        if((numOfWifi > 0) && (numOfWifi < 3)){
                              digitalWrite(KXN_LED_DEFAULT, KXN_LED_ACTIVE_DEFAULT);
                              delay(1000);
                              digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);
                              delay(1000);
                              digitalWrite(KXN_LED_DEFAULT, KXN_LED_ACTIVE_DEFAULT);
                              delay(1000);
                              digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);
                              delay(1000);
                        }else if(numOfWifi <= 0){
                              digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);
                              delay(2000);
                        }else{
                              for(int cff = 0; cff <10; cff++){
                                    digitalWrite(KXN_LED_DEFAULT, KXN_LED_ACTIVE_DEFAULT);
                                    delay(100);
                                    digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);
                                    delay(100);
                              }
                        }
                  } 
            }
      #endif

      void Task2code( void * pvParameters ){
      Serial.print("Task2 running on core ");
      Serial.println(xPortGetCoreID());
      // Set WiFi to station mode and disconnect from an AP if it was previously connected.
      WiFi.mode(WIFI_STA);
      WiFi.disconnect();
      delay(100);

      Serial.println("Setup done");

      for(;;){
            Serial.println("Scan start");

            // WiFi.scanNetworks will return the number of networks found.
            int n = WiFi.scanNetworks();
            Serial.println("Scan done");
            numOfWifi = n;
            if (n == 0) {
                  Serial.println("no networks found");
            } else {
                  Serial.print(n);
                  Serial.println(" networks found");
                  Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
                  for (int i = 0; i < n; ++i) {
                        // Print SSID and RSSI for each network found
                        Serial.printf("%2d",i + 1);
                        Serial.print(" | ");
                        Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
                        Serial.print(" | ");
                        Serial.printf("%4d", WiFi.RSSI(i));
                        Serial.print(" | ");
                        Serial.printf("%2d", WiFi.channel(i));
                        Serial.print(" | ");
                        switch (WiFi.encryptionType(i))
                        {
                        case WIFI_AUTH_OPEN:
                        Serial.print("open");
                        break;
                        case WIFI_AUTH_WEP:
                        Serial.print("WEP");
                        break;
                        case WIFI_AUTH_WPA_PSK:
                        Serial.print("WPA");
                        break;
                        case WIFI_AUTH_WPA2_PSK:
                        Serial.print("WPA2");
                        break;
                        case WIFI_AUTH_WPA_WPA2_PSK:
                        Serial.print("WPA+WPA2");
                        break;
                        case WIFI_AUTH_WPA2_ENTERPRISE:
                        Serial.print("WPA2-EAP");
                        break;
                        case WIFI_AUTH_WPA3_PSK:
                        Serial.print("WPA3");
                        break;
                        case WIFI_AUTH_WPA2_WPA3_PSK:
                        Serial.print("WPA2+WPA3");
                        break;
                        case WIFI_AUTH_WAPI_PSK:
                        Serial.print("WAPI");
                        break;
                        default:
                        Serial.print("unknown");
                        }
                        Serial.println();
                        delay(10);
                  }
            }
            Serial.println("");

            // Delete the scan result to free memory for code below.
            WiFi.scanDelete();
            delay(2000);
            
            } 
      }

      void ESP32_scanWiFi_init(){
            xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2ScanWF",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
            delay(500); 

            xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1BlinkLed",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */                  
            delay(500); 
      }

      
      // #define VIETDUINO_ESP32_TYPEC_V1

      #if defined(VIETDUINO_ESP32)
            pin_info my_pin_array[] = {
                  // {LastValue,       pin,        type,                   mode,         posOnchip,      name},
                  {1,               16,         _PIN_TYPE_D_,           MODE_PIN_IO,         27 ,     "D2"},
                  {2,               17,         _PIN_TYPE_D_,           MODE_PIN_IO,         28,      "D3"},
                  {3,               25,         _PIN_TYPE_D_,           MODE_PIN_IO,         10,      "D4"},
                  {4,               26,         _PIN_TYPE_D_,           MODE_PIN_IO,         11,      "D5"},
                  {5,               27,         _PIN_TYPE_D_,           MODE_PIN_IO,         12,      "D6"},
                  {6,               14,         _PIN_TYPE_D_,           MODE_PIN_IO,         13,      "D7"},
                  {7,               2,          _PIN_TYPE_D_,           MODE_PIN_IO,         24,      "D8"},
                  {8,               13,         _PIN_TYPE_D_,           MODE_PIN_IO,         16,      "D9"},
                  {9,               5,          _PIN_TYPE_D_,           MODE_PIN_IO,         29,      "D10"},
                  {10,              23,         _PIN_TYPE_D_,           MODE_PIN_IO,         37,      "D11"},
                  {11,              19,         _PIN_TYPE_D_,           MODE_PIN_IO,         31,      "D12"},
                  {12,              18,         _PIN_TYPE_D_,           MODE_PIN_IO,         30,      "D13"},
                  {13,              35,         _PIN_TYPE_A_,           MODE_PIN_I,          7,       "A0"},
                  {14,              34,         _PIN_TYPE_A_,           MODE_PIN_I,          6,       "A1"},
                  {15,              33,         _PIN_TYPE_A_,           MODE_PIN_IO,         9,       "A2"},
                  {16,              32,         _PIN_TYPE_A_,           MODE_PIN_IO,         8,       "A3"},
                  {17,              4,          _PIN_TYPE_A_,           MODE_PIN_IO,         26,      "A4"},
                  {18,              15,         _PIN_TYPE_A_,           MODE_PIN_IO,         23,      "A5"},
                  {19,              22,         _PIN_TYPE_D_,           MODE_PIN_IO,         36,      "F2"},
                  {20,              21,         _PIN_TYPE_D_,           MODE_PIN_IO,         33,      "F1"},
                  {21,              0 ,         _PIN_TYPE_D_,           MODE_PIN_IO,         25,      "F0"}

            };
      
      #elif defined(VIETDUINO_ESP32S3_N16R8) || defined(ESP32S3_N16R8_DEVKIT)
      pin_info my_pin_array[] = {
      {1,    7,   _PIN_TYPE_D_,   MODE_PIN_IO,    7,   "D2"},
      {2,    14,    _PIN_TYPE_D_,    MODE_PIN_IO,   14,   "D3"},
      {3,    15,    _PIN_TYPE_D_,    MODE_PIN_IO,   8,    "D4"},
      {4,    16,    _PIN_TYPE_D_,    MODE_PIN_IO,   9,    "D5"},
      {5,    17,    _PIN_TYPE_D_,    MODE_PIN_IO,   10,   "D6"},
      {6,    18,    _PIN_TYPE_D_,    MODE_PIN_IO,   12,   "D7"},
      {7,    21,    _PIN_TYPE_D_,    MODE_PIN_IO,   22,   "D8"},
      {8,    38,    _PIN_TYPE_D_,    MODE_PIN_IO,   30,   "D9"},
      {9,    10,    _PIN_TYPE_D_,    MODE_PIN_IO,   18,   "D10"},
      {10,   11,   _PIN_TYPE_D_,   MODE_PIN_IO,    19,    "D11"},
      {11,   13,   _PIN_TYPE_D_,   MODE_PIN_IO,    21,    "D12"},
      {12,   12,   _PIN_TYPE_D_,   MODE_PIN_IO,    20,    "D13"},
      {13,   1,    _PIN_TYPE_A_,    MODE_PIN_IO,    33,    "A0"},
      {14,   2,    _PIN_TYPE_A_,    MODE_PIN_IO,    37,    "A1"},
      {15,   3,    _PIN_TYPE_A_,    MODE_PIN_IO,   15,    "A2"},
      {16,   4,    _PIN_TYPE_A_,    MODE_PIN_IO,   4,     "A3"},
      {17,   5,    _PIN_TYPE_A_,    MODE_PIN_IO,   5,     "A4"},
      {18,   6,    _PIN_TYPE_A_,    MODE_PIN_IO,   6,     "A5"},
      {19,   39,   _PIN_TYPE_D_,   MODE_PIN_IO,    31,    "39"},
      {20,   40,   _PIN_TYPE_D_,   MODE_PIN_IO,    40,    "40"},
      {21,   41,   _PIN_TYPE_D_,   MODE_PIN_IO,    25,    "41"},
      {22,   42,   _PIN_TYPE_D_,   MODE_PIN_IO,    34,    "42"},
      {23,   47,   _PIN_TYPE_D_,   MODE_PIN_IO,    23,    "47"},
      // {24,   48,   _PIN_TYPE_D_,   MODE_PIN_IO,    24,    "48"},
      {25,   8,    _PIN_TYPE_D_,    MODE_PIN_IO,   12,   "8DA"},
      {26,   9,    _PIN_TYPE_D_,    MODE_PIN_IO,   17,   "9CL"},
      {27,   0,    _PIN_TYPE_D_,    MODE_PIN_IO,   27,   "IO0"},

      };
      #else

            pin_info my_pin_array[] = {
      //{LastValue,                               pin,                         type,                        mode,                        posOnchip,                        name},
            {1,                           25,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       10,                        "D2"},
            {2,                           26,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       11,                        "D3"},
            {3,                           17,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       28,                        "D4"},
            {4,                           16,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       27,                        "D5"},
            {5,                           27,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       12,                        "D6"},
            {6,                           14,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       13,                        "D7"},
            {7,                           12,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       14,                        "D8"},
            {8,                           13,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       16,                        "D9"},
            {9,                           5,                           _PIN_TYPE_D_,                      MODE_PIN_IO,                       29,                        "D10"},
            {10,                          23,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       37,                        "D11"},
            {11,                          19,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       31,                        "D12"},
            {12,                          18,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       30,                        "D13"},
            {13,                          35,                          _PIN_TYPE_A_,                      MODE_PIN_I,                        7,                         "A0"},
            {14,                          4,                           _PIN_TYPE_A_,                      MODE_PIN_IO,                       26,                        "A1"},
            {15,                          33,                          _PIN_TYPE_A_,                      MODE_PIN_IO,                       9,                         "A2"},
            {16,                          32,                          _PIN_TYPE_A_,                      MODE_PIN_IO,                       8,                         "A3"},
            {17,                          2,                           _PIN_TYPE_A_,                      MODE_PIN_IO,                       24,                        "A4"},
            {18,                          15,                          _PIN_TYPE_A_,                      MODE_PIN_IO,                       23,                        "A5"},
            {19,                          22,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       36,                        "F2"},
            {20,                          21,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       33,                        "F1"},
            {21,                          0 ,                          _PIN_TYPE_D_,                      MODE_PIN_IO,                       25,                        "F0"}

            };
      #endif
#elif defined(CORE_ESP8266_FEATURES_H)
            
      #include <ESP8266WiFi.h>

      #if defined(NODEMCU_ESP8266)
            pin_info my_pin_array[] = {
                  // {LastValue,       pin,        type,                   mode,         posOnchip,      name},
                  {1,               0,          _PIN_TYPE_D_,           MODE_PIN_IO,          18,        "D3"},
                  {2,               2,          _PIN_TYPE_D_,           MODE_PIN_IO,          17,        "D4"},
                  {3,               4,          _PIN_TYPE_D_,           MODE_PIN_IO,          19,        "D2"},
                  {4,               5,          _PIN_TYPE_D_,           MODE_PIN_IO,          20,        "D1"},
                  {5,               12,         _PIN_TYPE_D_,           MODE_PIN_IO,          6,        "D6"},
                  {6,               13,         _PIN_TYPE_D_,           MODE_PIN_IO,          7,        "D7"},
                  {7,               14,         _PIN_TYPE_D_,           MODE_PIN_IO,          5,        "D5"},
                  {8,               15,         _PIN_TYPE_D_,           MODE_PIN_I,          16,       "D15"},
                  {9,               16,         _PIN_TYPE_D_,           MODE_PIN_I,          4,        "D0"},


            };
      #else
            pin_info my_pin_array[] = {
                  // {LastValue,       pin,        type,                   mode,         posOnchip,      name},
                  {1,               0,          _PIN_TYPE_D_,           MODE_PIN_IO,          18,        "0"},
                  {2,               2,          _PIN_TYPE_D_,           MODE_PIN_IO,          17,        "2"},
                  {3,               4,          _PIN_TYPE_D_,           MODE_PIN_IO,          19,        "4"},
                  {4,               5,          _PIN_TYPE_D_,           MODE_PIN_IO,          20,        "5"},
                  {5,               12,         _PIN_TYPE_D_,           MODE_PIN_IO,          6,        "12"},
                  {6,               13,         _PIN_TYPE_D_,           MODE_PIN_IO,          7,        "13"},
                  {7,               14,         _PIN_TYPE_D_,           MODE_PIN_IO,          5,        "14"},
                  {8,               15,         _PIN_TYPE_D_,           MODE_PIN_I,          16,       "15"},
                  {9,               16,         _PIN_TYPE_D_,           MODE_PIN_I,          4,        "16"},


            };
      #endif
      // bool ledActive = 1;

      void ESP8266_blinkLed(int numOfWifi){
            if((numOfWifi > 0) && (numOfWifi < 3)){
                  digitalWrite(KXN_LED_DEFAULT, KXN_LED_ACTIVE_DEFAULT);
                  delay(1000);
                  digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);
                  delay(1000);
                  digitalWrite(KXN_LED_DEFAULT, KXN_LED_ACTIVE_DEFAULT);
                  delay(1000);
                  digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);
                  delay(1000);
            }else if(numOfWifi <= 0){
                  digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);
                  delay(2000);
            }else{
                  for(int cff = 0; cff <10; cff++){
                        digitalWrite(KXN_LED_DEFAULT, KXN_LED_ACTIVE_DEFAULT);
                        delay(100);
                        digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);
                        delay(100);
                  }
            }
      }

      void ESP8266_BlinkScanWiFi(){
            Serial.println(F("\nESP8266 WiFi scan example"));

            // Set WiFi to station mode
            WiFi.mode(WIFI_STA);

            // Disconnect from an AP if it was previously connected
            WiFi.disconnect();
            delay(100);

            
            pinMode(KXN_LED_DEFAULT, OUTPUT);
            digitalWrite(KXN_LED_DEFAULT, !KXN_LED_ACTIVE_DEFAULT);

            while(1){
                  String ssid;
                  int32_t rssi;
                  uint8_t encryptionType;
                  uint8_t* bssid;
                  int32_t channel;
                  bool hidden;
                  int scanResult;

                  Serial.println(F("Starting WiFi scan..."));

                  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

                  if (scanResult == 0) {
                  Serial.println(F("No networks found"));
                  } else if (scanResult > 0) {
                  Serial.printf(PSTR("%d networks found:\n"), scanResult);

                  // Print unsorted scan results
                  for (int8_t i = 0; i < scanResult; i++) {
                        WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel, hidden);

                        Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
                                    i,
                                    channel,
                                    bssid[0], bssid[1], bssid[2],
                                    bssid[3], bssid[4], bssid[5],
                                    rssi,
                                    (encryptionType == ENC_TYPE_NONE) ? ' ' : '*',
                                    hidden ? 'H' : 'V',
                                    ssid.c_str());
                        delay(0);
                  }
                  } else {
                  Serial.printf(PSTR("WiFi scan error %d"), scanResult);
                  }

                  // Wait a bit before scanning again
                  // delay(2000);
                  ESP8266_blinkLed(scanResult);
            }
      }
#endif

uint16_t sizeArray = sizeof(my_pin_array)/sizeof(pin_info);