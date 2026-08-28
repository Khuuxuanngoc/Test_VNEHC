#ifndef variable_board_h_
#define variable_board_h_
#include "Arduino.h"

/**
 * @brief Uncomment to Enable your board
 * 
 */
// Step 1 
//#define MTINY_ESP8266
// #define NODEMCU_ESP8266
// #define VIETDUINO_ESP32
// #define VIETDUINO_ESP32S3_N16R8
#define ESP32S3_N16R8_DEVKIT


#if defined(ARDUINO_AVR_ADK)       
    #define BOARD "Mega Adk"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_BT)    // Bluetooth
    #define BOARD "Bt"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_DUEMILANOVE)       
    #define BOARD "Duemilanove"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_ESPLORA)       
    #define BOARD "Esplora"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_ETHERNET)       
    #define BOARD "Ethernet"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_FIO)       
    #define BOARD "Fio"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_GEMMA)
    #define BOARD "Gemma"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_LEONARDO)       
    #define BOARD "Leonardo"
    #define NUM_DIGITAL_PINS_2        20
#elif defined(ARDUINO_AVR_LILYPAD)
    #define BOARD "Lilypad"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_LILYPAD_USB)
    #define BOARD "Lilypad Usb"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_MEGA)
    #define BOARD "Mega"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_MEGA2560)       
    #define BOARD "Mega 2560"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_MICRO)       
    #define BOARD "Micro"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_MINI)       
    #define BOARD "Mini"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_NANO)       
    #define BOARD "Nano"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_NG)       
    #define BOARD "NG"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_PRO)       
    #define BOARD "Pro Mini"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_ROBOT_CONTROL)       
    #define BOARD "Robot Ctrl"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_ROBOT_MOTOR)       
    #define BOARD "Robot Motor"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_UNO)       
    #define BOARD "Uno"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_AVR_YUN)       
    #define BOARD "Yun"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS

// These boards must be installed separately:
#elif defined(ARDUINO_SAM_DUE)       
    #define BOARD "Due"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_SAMD_ZERO)       
    #define BOARD "Zero"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
#elif defined(ARDUINO_ARC32_TOOLS)       
    #define BOARD "101"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS

#elif defined(ARDUINO_ARCH_ESP32)
    #if defined(MTINY_ESP32)
        #define BOARD "ESP32-Wroom (Vietduino ESP32)"
        #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
        #define KXN_LED_DEFAULT     2
        #define KXN_LED_ACTIVE_DEFAULT      0
    #elif defined(VIETDUINO_ESP32)
        #define BOARD "ESP32-Wroom (Vietduino ESP32)"
        #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
        #define KXN_LED_DEFAULT     18
        #define KXN_LED_ACTIVE_DEFAULT      1
    #elif defined(VIETDUINO_ESP32S3_N16R8)
        #define BOARD "VIETDUINO_ESP32S3_N16R8"
        #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
        #define KXN_LED_DEFAULT     12
        #define KXN_LED_ACTIVE_DEFAULT      1

    #elif defined(ESP32S3_N16R8_DEVKIT)
        #define BOARD "ESP32S3_N16R8_DEVKIT"
        #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
        #define KXN_LED_DEFAULT    48
        #define KXN_LED_ACTIVE_DEFAULT      1
    
    #endif
#elif defined(ARDUINO_ARCH_ESP8266)
    #define BOARD "ESP8266"
    #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
    #if defined(MTINY_ESP8266) || defined(NODEMCU_ESP8266)
        #define KXN_LED_DEFAULT     2
        #define KXN_LED_ACTIVE_DEFAULT      1
    #endif
#else
    #error "Unknown board"
#endif

  #if defined(HSHOP_TEST_BOARD_MEGA2560_PRO_EMBED_BLACK)       
        #define BOARD "Mega2560 Pro Embed"
        #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
  #elif defined(HSHOP_TEST_BOARD_MEGA2560_WIFI_BLACK)
        #define BOARD "Mega2560 WiFi"
        #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
  #elif defined(HSHOP_TEST_BOARD_UNO_WIFI_BLACK)
        #define BOARD "Uno WiFi"
        #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS
  #endif

    // #define BOARD "Uno WiFi"
    // #define NUM_DIGITAL_PINS_2        NUM_DIGITAL_PINS

#define STOP_PIN_DEFAULT_MICRO    23
#define STOP_PIN_DEFAULT    NUM_DIGITAL_PINS_2 - 1

enum{
    _PIN_TYPE_A_ = 0,
    _PIN_TYPE_D_
};

enum{
    MODE_PIN_O = 0, // only output
    MODE_PIN_I,     // only input 
    MODE_PIN_IA,    // only input analog
    MODE_PIN_IO     // input and output
};

#if defined(ARDUINO_ARCH_ESP32)
    typedef struct pin_info{
    uint8_t lastValue;
    uint8_t pin;
    uint8_t type;
    uint8_t mode;
    uint8_t posOnChip;
    uint8_t name[4];
    bool lastError;
    };
    extern void ESP32_scanWiFi_init();
#else
    typedef struct pin_info{
    uint8_t lastValue;
    uint8_t pin;
    uint8_t type;
    uint8_t mode;
    uint8_t posOnChip;
    uint8_t name[4];
    bool lastError;
    };
#endif

extern pin_info my_pin_array[];

extern uint16_t sizeArray;
extern int ledpin;
extern void ESP8266_BlinkScanWiFi();

#endif
