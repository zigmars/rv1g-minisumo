#include <Arduino.h>
#include <cstdint>
#include "rgb_leds.h"
#include "buttons.h"
#include "oled.h"

void swap(uint8_t &a, uint8_t &b) {
  uint8_t tmpA = a;
  a = b;
  b = tmpA;
}

void hardwareTest(void) {
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  //  digitalWrite(PIN_LED_RED, HIGH);

  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, HIGH);
  tone(PIN_BUZZER, 220, 20);

  uint8_t rgb_val = 10;
  for (int c = 0; c < 3; c++) {
    //    digitalWrite(PIN_LED_RED, LOW);
    //    digitalWrite(PIN_LED_GREEN, LOW);
    for (int i = 0; i < COUNT_LED_NEO; i++) {
      switch (c) {
        case 0:
          strip.setPixelColor(i, rgb_val, 0, 0);
          break;
        case 1:
          strip.setPixelColor(i, 0, rgb_val, 0);
          break;
        case 2:
          strip.setPixelColor(i, 0, 0, rgb_val);
          break;
        default:
          break;
          //strip.setPixelColor(i, 0, 0, 0);
      }
    }

    strip.show();

    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_GREEN, LOW);


    delay(300);
    digitalWrite(PIN_LED_RED, HIGH);
  }
  clearRGB();

  if (getButtonState(UpButton) == Pressed && getButtonState(DownButton) == Pressed) {
    while (getButtonState(UpButton) == Pressed || getButtonState(DownButton) == Pressed) {
      for (int i = 0; i < COUNT_LED_NEO; i++) {
        strip.setPixelColor(i, getButtonState(UpButton) == Pressed ? 10 : 0, getButtonState(DownButton) == Pressed ? 5 : 0, getButtonState(RightButton) == Pressed ? 20 : 0);
      }
      strip.show();
    }
    clearRGB();
  }
}

static uint16_t ADC_BATT_offset = 35;
static uint16_t ADC_BATT_fullScale = 4095;

static void showCalTitle(){
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.println(F("Calibration"));
}

void calibrateBattAdcOffset(){
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  showCalTitle();
  oled.println(F("Hold Batt ADC to GND and press Right button"));
  oled.display();
  while(getButtonState(RightButton) == Released){
    if(getButtonState(UpButton) == Pressed){
      return;
    }
    oled.fillRect(0, 32, 6*4, 8, 0),
    oled.setCursor(0,32);
    oled.print(analogRead(PIN_ADC_BAT));
    oled.display();
    delay(100);
  }
  const uint16_t countPower = 8, count = (1<<countPower);
  uint32_t adcSum = 0;
  for(uint16_t i = 0; i < count; i++){
    adcSum += analogRead(PIN_ADC_BAT);
  }
  ADC_BATT_offset = (adcSum >> countPower);
  
  showCalTitle();
  oled.print(F("Cal value: "));
  oled.print(adcSum);
  oled.print(F(" "));
  oled.println(ADC_BATT_offset);
  
  oled.println(F("Hold Batt ADC to 3.3V and press Right button"));
  oled.display();
  while(getButtonState(RightButton) == Released){
    oled.fillRect(0, 40, 6*4, 8, 0),
    oled.setCursor(0, 40);
    oled.print(analogRead(PIN_ADC_BAT));
    oled.display();
    delay(100);
  }
  
  adcSum = 0;
  for(uint16_t i = 0; i < count; i++){
    adcSum += analogRead(PIN_ADC_BAT);
  }
  ADC_BATT_fullScale = adcSum >> countPower;
  
  showCalTitle();
  oled.print(F("Cal value: "));
  oled.println(ADC_BATT_offset);
  oled.print(F("3.3V value: "));
  oled.print(adcSum);
  oled.print(F(" "));
  oled.println(ADC_BATT_fullScale);
  oled.display();
  delay(3000);
}

float readVoltage(int pin){
  return 3.3f/((1<<ADC_RESOLUTION)-1) * (analogRead(pin)-ADC_BATT_offset);
}

float readBatteryVoltage(){
  return ( (3.30f * (10.f + 18.f)/10.f) / ((1<<ADC_RESOLUTION)-1) * (analogRead(PIN_ADC_BAT) - ADC_BATT_offset));
}
