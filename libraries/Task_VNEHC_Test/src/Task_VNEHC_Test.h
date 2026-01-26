#ifndef Task_VNEHC_Test_H__
#define Task_VNEHC_Test_H__

/**
 * @file Task_VNEHC_Test.h
 *    Qui trình kiểm tra VNEHC
 *        - Kiểm tra nguồn cấp cho mạch VNEHC
    *        - Khởi động, đo điện áp, dòng điện nguồn nuôi cho Port3 và Port4
    *        - Setup INA3221 để đo dòng điện qua Shunt 0.1 Ohm
    *        - Setup ngưỡng dòng điện nguy cấp (Critical) tùy theo loại mạch đang được cắm vào.
    *        - Bật Fet-P (nằm sau Shunt) cấp nguồn 5V cho Port3 và Port4
    *        - Ngắt nguồn nếu dòng điện vượt quá 40mA (Kiểm tra chân Critical của INA3221)
    *     - Đo Mức điện áp tại các chân SIGNAL của Port3 và Port4
    *       - Đối với các mạch có sẵn trở kéo lên 3V3 thì ADC đọc được mức điện áp ~3.3V
    *       - Đối với các mạch không có trở kéo lên 3V3
    *     - Bắt đầu Test và giám sát chân CRITICAL của INA3221, ngắt nguồn nếu vượt quá ngưỡng của các trường hợp test
    *       - Hiển thị các Kết quả qua UART:
    *         - Mức điện áp tại chân SIGNAL của Port3 và Port4
    *         - Mức dòng điện qua Shunt (tương ứng với Port3 và Port4)
    *         - 
 */

#include "kxnTask.h"
#include "VNEHC_List_Error.h"
#include "INA3221.h"
#include "Wire.h"

// Pin điều khiển Fet N để cấp nguồn cho Port3 và Port4
#define PIN_FET_N   7
#define FET_N_ACTIVE    1

#define PIN_INA_CRI       A3
#define PIN_PORT3_SIG     A0
#define PIN_PORT4_SDA     A4
#define PIN_PORT4_SCL     A5
#define PIN_PORT4_RX      A1
#define PIN_PORT4_TX      A2

#define PIN_VNEHC_PWR_OUT_3V6   6
#define PIN_VNEHC_PWR_OUT_3V6_ACTIVE   1

#define PIN_VNEHC_PWR_OUT_0   6
#define PIN_VNEHC_PWR_OUT_0_ACTIVE   1
#define PIN_VNEHC_PWR_OUT_1   5
#define PIN_VNEHC_PWR_OUT_1_ACTIVE   1
#define PIN_VNEHC_PWR_OUT_2   4
#define PIN_VNEHC_PWR_OUT_2_ACTIVE   1

#define ADC_RESOLUTION    1023.0
#define ADCVALUE_3V3_THRESHOLD   720   // ~3.3V
#define ADCVALUE_PULL_UP_THRESHOLD   6832   
#define ADCVALUE_PULL_UP_THRESHOLD_ERROR   150 // FIX BUG when 3.34V  

// Safe voltage range for VNEHC power input
#define INA_VOLTAGE_SAFE_MAX_mV   5100
#define INA_VOLTAGE_SAFE_MIN_mV   (INA_VOLTAGE_SAFE_MAX_mV*90/100)
#define INA_CURRENT_SAFE_MAX_mA   40

#define IS_INRANGE(val, min, max)   ((val >= min) && (val <= max))

// Macro for log output
#define VNEHC_SHOW_LOG(...)     if(VNEHC_Serial) { VNEHC_Serial->print(__VA_ARGS__); }
#define VNEHC_SHOW_LOG_LN(...)     if(VNEHC_Serial) { VNEHC_Serial->println(__VA_ARGS__); }

CREATE_TASK_STATE(Task_VNEHC_Test)
Task_VNEHC_Test_CHECK_POWER_CURRENT
END

CREATE_TASK(Task_VNEHC_Test)
INA3221 *INA;
TwoWire *VNEHC_Wire;
Stream *VNEHC_Serial;
void (*user_callback_help)(void);
void (*user_callback_OverCurrrent)(float current_mA);

void restart()
{
  void(* resetFunc) (void) = 0; // Khai bao mot ham tai dia chi 0
  resetFunc();
}

uint8_t setup(TwoWire *wire = &Wire, Stream *serial = &Serial)
{
  VNEHC_Wire = wire;
  VNEHC_Serial = serial;
  OutPWR_setup();

  VNEHC_Wire->begin();
  if(INA == NULL)
  {
    INA = new INA3221(0x40, VNEHC_Wire);
    if(!INA->begin())
    {
      OutPWR_off();
      VNEHC_SHOW_LOG_LN(F("I2C port Error!"));
      return VNEHC_List_Error_I2C;
    }

    INA->setShuntR(0, 0.100);
    INA->setShuntR(1, 0.100);
    INA->setShuntR(2, 0.100);
  }

  kxnTaskManager.add(this);
  setState(0);
  kDelay(0);
  return VNEHC_List_Error_None;
}

void OutPWR_setup()
{
  pinMode(PIN_FET_N, OUTPUT);
  // digitalWrite(PIN_FET_N, !FET_N_ACTIVE);
  OutPWR_on();
  
  // pinMode(PIN_VNEHC_PWR_OUT_3V6, OUTPUT);
  // setOutPWR_3V6(1);

  pinMode(PIN_VNEHC_PWR_OUT_0, OUTPUT);
  pinMode(PIN_VNEHC_PWR_OUT_1, OUTPUT);
  pinMode(PIN_VNEHC_PWR_OUT_2, OUTPUT);
  digitalWrite(PIN_VNEHC_PWR_OUT_0, !PIN_VNEHC_PWR_OUT_0_ACTIVE);
  digitalWrite(PIN_VNEHC_PWR_OUT_1, !PIN_VNEHC_PWR_OUT_1_ACTIVE);
  digitalWrite(PIN_VNEHC_PWR_OUT_2, !PIN_VNEHC_PWR_OUT_2_ACTIVE);
  // delay(10);
  OutPWR_on();
}

void OutPWR_on()
{
  digitalWrite(PIN_FET_N, FET_N_ACTIVE);
}

void OutPWR_off()
{
  digitalWrite(PIN_FET_N, !FET_N_ACTIVE);
}

uint8_t setOutPWR_5V()
{
  this->OutPWR_off();
  this->delayms(5);
  digitalWrite(PIN_VNEHC_PWR_OUT_0, !PIN_VNEHC_PWR_OUT_0_ACTIVE);
  digitalWrite(PIN_VNEHC_PWR_OUT_1, !PIN_VNEHC_PWR_OUT_1_ACTIVE);
  digitalWrite(PIN_VNEHC_PWR_OUT_2, !PIN_VNEHC_PWR_OUT_2_ACTIVE);

  this->delayms(10);

  return VNEHC_List_Error_None;
}

void setOutPWR_3V6(bool onoff)
{
  if(onoff)
  {
    OutPWR_off();
    delay(10);
    digitalWrite(PIN_VNEHC_PWR_OUT_3V6, PIN_VNEHC_PWR_OUT_3V6_ACTIVE);
    delay(120);
    OutPWR_on();
    delay(10);
  }
  else
  {
    OutPWR_off();
    delay(10);
    digitalWrite(PIN_VNEHC_PWR_OUT_3V6, !PIN_VNEHC_PWR_OUT_3V6_ACTIVE);
    delay(10);
  }
}

void setSaftyVol_mV(uint32_t pa_mv)
{
  float tempVolt = INA->getBusVoltage(0);  // Volt
}

void loop()
{
  // for (int ch = 0; ch < 1; ch++)
  // {
  //   VNEHC_SHOW_LOG(ch);
  //   VNEHC_SHOW_LOG("\t");
  //   VNEHC_SHOW_LOG(INA->getBusVoltage(ch), 3);
  //   VNEHC_SHOW_LOG("\t");
  //   // VNEHC_SHOW_LOG(INA->getShuntVoltage_mV(ch), 3);
  //   // VNEHC_SHOW_LOG("\t");
  //   VNEHC_SHOW_LOG(INA->getCurrent_mA(ch), 3);
  //   VNEHC_SHOW_LOG("\t");
  //   // VNEHC_SHOW_LOG(INA->getPower_mW(ch), 3);
  //   VNEHC_SHOW_LOG_LN();
  //   kDelay(100);
  //   // if(INA->getCurrent_mA(ch) >= 40)
  //   // {
  //   //   // digitalWrite(PIN_FET_N, !FET_N_ACTIVE);
  //   // }
  //   // delay(1000);
  // }

  this->checkOverCurrent();
  this->checkSerial();
  kDelay(10);
}

bool INA_checkPinCritical_OK()
{
  float current = INA->getCurrent_mA(0);
  if(analogRead(PIN_INA_CRI) <= 200)  // Pin Critical active LOW
  {
    return false;   // Over Current
  }
  return true;
}

void checkOverCurrent(void *user_callback(void)=NULL)
{
  if(INA_checkPinCritical_OK() == false)
  {
    float tempCurrent = INA->getCurrent_mA(0);
    OutPWR_off();
    VNEHC_SHOW_LOG(F("VNEHC Test: Over Current detected! "));
    // VNEHC_SHOW_LOG(String() + tempCurrent);
    VNEHC_SHOW_LOG_LN(String() + tempCurrent + "/" + INA->getCriticalCurrent(0));
    if(user_callback != NULL)
    {
      user_callback();
    }
    if(this->user_callback_OverCurrrent != NULL)
    {
      this->user_callback_OverCurrrent(tempCurrent);
    }
    // while(1); // y260117 - commented out to avoid blocking
  }
}

uint8_t checkCurrent_mA(float currentLimit_mA)
{
  INA->setCriticalCurrent(0, currentLimit_mA);  // chanel 0 200mA
  this->OutPWR_on();
  delay(5);
  
  // if(INA_checkPinCritical_OK() == false)
  // {
  //   this->OutPWR_off();
  //   VNEHC_SHOW_LOG(F("VNEHC Test: Over Current detected!"));
  //   VNEHC_SHOW_LOG_LN(INA->getCurrent_mA(0));
  //   return VNEHC_List_Error_PWR_OVER_CURRENT;
  // }

  this->checkOverCurrent();
  this->kDelay(10);

  return VNEHC_List_Error_None;
}

uint8_t checkVoltageCurrent()
{
  OutPWR_off();
  delay(10);

  // Check VCC Voltage
  float TempVin = INA->getBusVoltage_mV(0);
  if(TempVin < INA_VOLTAGE_SAFE_MIN_mV)
  {

    VNEHC_SHOW_LOG(F("VNEHC Test: mVol too low: "));
    VNEHC_SHOW_LOG_LN(String(TempVin));
    return VNEHC_List_Error_PWR_VOLT_LOWER;
  }
  else if(TempVin > INA_VOLTAGE_SAFE_MAX_mV)
  {
    VNEHC_SHOW_LOG(F("VNEHC Test: mVol too high: "));
    VNEHC_SHOW_LOG_LN(String(TempVin));
    return VNEHC_List_Error_PWR_VOLT_HIGHER;
  }
  else
  {
    VNEHC_SHOW_LOG(F("VNEHC Test: VCC OK: "));
    VNEHC_SHOW_LOG_LN(String(TempVin));
  }

  INA->setCriticalCurrent(0, 200);  // chanel 0 200mA
  OutPWR_on();
  delay(10);
  
  // if(INA_checkPinCritical_OK() == false)
  // {
  //   OutPWR_off();
  //   VNEHC_SHOW_LOG(F("VNEHC Test: Over Current detected! "));
  //   VNEHC_SHOW_LOG_LN(INA->getCurrent_mA(0));
  //   return VNEHC_List_Error_PWR_OVER_CURRENT;
  // }
  this->checkOverCurrent();

  return VNEHC_List_Error_None;
}

uint8_t checkVoltageCurrent(void *user_callback(void))
{
  OutPWR_off();
  delay(10);

  // Check VCC Voltage
  float TempVin = INA->getBusVoltage_mV(0);
  if(TempVin < INA_VOLTAGE_SAFE_MIN_mV)
  {

    VNEHC_SHOW_LOG(F("VNEHC Test: mVol too low: "));
    VNEHC_SHOW_LOG_LN(String(TempVin));
    return VNEHC_List_Error_PWR_VOLT_LOWER;
  }
  else if(TempVin > INA_VOLTAGE_SAFE_MAX_mV)
  {
    VNEHC_SHOW_LOG(F("VNEHC Test: mVol too high: "));
    VNEHC_SHOW_LOG_LN(String(TempVin));
    return VNEHC_List_Error_PWR_VOLT_HIGHER;
  }
  else
  {
    VNEHC_SHOW_LOG(F("VNEHC Test: VCC OK: "));
    VNEHC_SHOW_LOG_LN(String(TempVin));
  }

  INA->setCriticalCurrent(0, 300);  // chanel 0 200mA
  OutPWR_on();
  delay(10);
  
  // if(INA_checkPinCritical_OK() == false)
  // {
  //   OutPWR_off();
  //   VNEHC_SHOW_LOG(F("VNEHC Test: Over Current detected! "));
  //   VNEHC_SHOW_LOG_LN(INA->getCurrent_mA(0));
  //   return VNEHC_List_Error_PWR_OVER_CURRENT;
  // }

  this->checkOverCurrent(user_callback);

  return VNEHC_List_Error_None;
}

uint8_t checkVolSignal3P(uint8_t paFlagDebug=0)
{
  pinMode(PIN_PORT3_SIG, INPUT);
  delay(10);
  int adcValue = analogRead(PIN_PORT3_SIG);

  // if(IS_INRANGE(adcValue, ADCVALUE_3V3_THRESHOLD - 100, ADCVALUE_3V3_THRESHOLD + 100) == false)
  if(adcValue < (ADCVALUE_3V3_THRESHOLD - 100))
  {
    if(paFlagDebug)
    {
      VNEHC_SHOW_LOG_LN(F("BUGGGG"));
      VNEHC_SHOW_LOG(F("Volt PORT3 < 3V3 :"));
      VNEHC_SHOW_LOG_LN(String(adcValue * (5.0 / ADC_RESOLUTION), 3));
    }
    
    return VNEHC_List_Error_SIG_LOWER_3V3;
  }
  else if(adcValue > (ADCVALUE_3V3_THRESHOLD + 100))
  {
    if(paFlagDebug)
    {
      VNEHC_SHOW_LOG_LN(F("BUGGGG"));
      VNEHC_SHOW_LOG(F("Volt PORT3 > 3V3 :"));
      VNEHC_SHOW_LOG_LN(String(adcValue * (5.0 / ADC_RESOLUTION), 3));
    }
    
    return VNEHC_List_Error_SIG_OVER_3V3;
  }
  else
  {
    VNEHC_SHOW_LOG(F("Volt PORT3 3V3 OK :"));
    VNEHC_SHOW_LOG_LN(String(adcValue * (5.0 / ADC_RESOLUTION), 3));
  }
  return VNEHC_List_Error_None;
}

uint8_t checkVolSignal4P()
{
  pinMode(PIN_PORT4_SDA, INPUT);
  pinMode(PIN_PORT4_SCL, INPUT);
  delay(10);
  int adcValue_SDA = analogRead(PIN_PORT4_SDA);
  int adcValue_SCL = analogRead(PIN_PORT4_SCL);
  if(adcValue_SDA > ADCVALUE_3V3_THRESHOLD || adcValue_SCL > ADCVALUE_3V3_THRESHOLD)
  {
    VNEHC_SHOW_LOG_LN(F("BUGGGG"))
    VNEHC_SHOW_LOG(F("Volt PORT4 not 3V3 :"));
    VNEHC_SHOW_LOG_LN(String(adcValue_SDA * (5.0 / ADC_RESOLUTION), 3) + "/" + String(adcValue_SCL * (5.0 / ADC_RESOLUTION), 3));
    return VNEHC_List_Error_SIG_NOT_3V3;
  }
  else
  {
    VNEHC_SHOW_LOG(F("Volt PORT4 3V3 OK :"));
    VNEHC_SHOW_LOG_LN(String(adcValue_SDA * (5.0 / ADC_RESOLUTION), 3) + "/" + String(adcValue_SCL * (5.0 / ADC_RESOLUTION), 3));
  }
  return VNEHC_List_Error_None;
}

uint8_t checkVolSignal4P_sSerial()
{
  pinMode(PIN_PORT4_RX, INPUT);
  pinMode(PIN_PORT4_TX, INPUT);
  delay(10);
  int adcValue_RX = analogRead(PIN_PORT4_RX);
  int adcValue_TX = analogRead(PIN_PORT4_TX);
  if(!IS_INRANGE(adcValue_RX, ADCVALUE_3V3_THRESHOLD - 100, ADCVALUE_3V3_THRESHOLD) || !IS_INRANGE(adcValue_TX, ADCVALUE_3V3_THRESHOLD - 100, ADCVALUE_3V3_THRESHOLD))
  {
    VNEHC_SHOW_LOG_LN(F("BUGGGG"))
    VNEHC_SHOW_LOG(F("Volt PORT4 sSerial not 3V3 (TX/RX):"));
    VNEHC_SHOW_LOG_LN(String(adcValue_RX * (5.0 / ADC_RESOLUTION), 3) + "/" + String(adcValue_TX * (5.0 / ADC_RESOLUTION), 3));
    return VNEHC_List_Error_SIG_NOT_3V3;
  }
  else
  {
    VNEHC_SHOW_LOG(F("Volt PORT4 sSerial 3V3 OK :"));
    VNEHC_SHOW_LOG_LN(String(adcValue_RX * (5.0 / ADC_RESOLUTION), 3) + "/" + String(adcValue_TX * (5.0 / ADC_RESOLUTION), 3));
  }
  return VNEHC_List_Error_None;
}

void delayms(uint32_t ms)
{
  uint32_t start = millis();
  uint32_t now = start;
  while (now - start < ms)
  {
    now = millis();
    kxnTaskManager.run(now);
  }
}

void addHelp(void *callback(void))
{
  user_callback_help = callback;
}

void addOverCurrentCallback(void (*callback(float current_mA)))
{
  user_callback_OverCurrrent = callback;
}

void checkSerial()
{
  if(VNEHC_Serial && VNEHC_Serial->available())
  {
    String tempCmd = VNEHC_Serial->readStringUntil('\n');
    VNEHC_Serial->println();
    VNEHC_Serial->println(F("----- VNEHC Test Help -----"));
    VNEHC_Serial->print(F("Your CMD: "));
    VNEHC_Serial->println(tempCmd);
    if(user_callback_help != NULL)
    {
      user_callback_help();
    }
  }
}

uint32_t sumAnalog_CheckPullDown_Port3()
{
  uint32_t tempui32 = 0;
  for(int cf =0; cf < 10; cf++)
  {
    tempui32 += analogRead(PIN_PORT3_SIG);
    this->delayms(1);
  }
  return tempui32;
}

uint8_t isPullDown_Port3_OK(uint8_t paShowDebug = 0, uint32_t paMin = 0, uint32_t paMax = 10)
{
  uint32_t tempui32 = this->sumAnalog_CheckPullDown_Port3();
  
  if(IS_INRANGE(tempui32, paMin, paMax))   // ~ 0.25V
  {
    return VNEHC_List_Error_None;
  }
  if(paShowDebug)
  {
    VNEHC_SHOW_LOG(F("R Pulldown ERROR: "));
    VNEHC_SHOW_LOG_LN(String(tempui32));
    // VNEHC_SHOW_LOG_LN(F("RESET Tool Test for next"));
  }
  return VNEHC_List_Error_PORT3_R_PULLDOWN_FAIL;
}

uint8_t isPullUp_Port3_OK(uint8_t paShowDebug = 0, uint32_t paMin = (ADCVALUE_PULL_UP_THRESHOLD - ADCVALUE_PULL_UP_THRESHOLD_ERROR), uint32_t paMax = (ADCVALUE_PULL_UP_THRESHOLD + ADCVALUE_PULL_UP_THRESHOLD_ERROR), uint32_t paTimeOutms = 10)
{
  uint32_t tempui32 = 0;
  while(paTimeOutms > 0)
  {
    tempui32 = this->sumAnalog_CheckPullDown_Port3();
    if(IS_INRANGE(tempui32, paMin, paMax))   // ~ 3V3
    {
      return VNEHC_List_Error_None;
    }
    this->delayms(10);
    paTimeOutms -= 10;
  }

  // uint32_t tempui32 = this->sumAnalog_CheckPullDown_Port3();
  
  // if(IS_INRANGE(tempui32, paMin, paMax))   // ~ 3V3
  // {
  //   return VNEHC_List_Error_None;
  // }

  if(paShowDebug)
  {
    VNEHC_SHOW_LOG(F("R Pull UP ERROR: "));
    VNEHC_SHOW_LOG_LN(String(tempui32));
    VNEHC_SHOW_LOG_LN(F("RESET Tool Test for next"));
  }
  
  return VNEHC_List_Error_PORT3_R_PULLUP_FAIL;
}

void setPort3_Output(bool onoff)
{
  pinMode(PIN_PORT3_SIG, OUTPUT);
  if(onoff)
  {
    digitalWrite(PIN_PORT3_SIG, PIN_VNEHC_PWR_OUT_0_ACTIVE);
  }
  else
  {
    digitalWrite(PIN_PORT3_SIG, !PIN_VNEHC_PWR_OUT_0_ACTIVE);
  }
}

float getPort3_mA()
{
  return INA->getCurrent_mA(0);
}

void showInfoWithErrorCode(VNEHC_List_Error errCode)
{
  VNEHC_SHOW_LOG(F("VNEHC Test Error Code: "));
  VNEHC_SHOW_LOG_LN(String(errCode));
  switch (errCode)
  {
  case VNEHC_List_Error_PORT3_R_PULLDOWN_FAIL:
    VNEHC_SHOW_LOG_LN(F(" - R Pulldown Port3 Fail"));
    break;
  
  default:
    break;
  }
}

void stop()
{
  this->OutPWR_off();
  while(1)
  {
    this->delayms(100);
  }
}

END

#endif