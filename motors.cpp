#include <Arduino.h>
#include <cstdint>
#include "utils.h"
#include "motors.h"

static void initMotorPins(void) {
  for (int i = 0; i < 4; i++) {
    pinMode(mtrPins[i], OUTPUT);
  }
}

void MotorPwmDrive(Motor mtr, DecayMode decay, MotorDirection dir, uint8_t power) {
  uint8_t pwmPin, constPin, pwmValue = power;
  if (dir == Backward) {
    pwmPin = mtr.pin1;
    constPin = mtr.pin2;
  } else {
    pwmPin = mtr.pin2;
    constPin = mtr.pin1;
  }
  if (decay == SlowDecay) {
    pwmValue = 255 - power;
    swap(pwmPin, constPin);
  }
  pinMode(constPin, OUTPUT);
  digitalWrite(constPin, (uint8_t)decay);
  analogWrite(pwmPin, pwmValue);
}

/*
static uint8_t selectedMenuIdx = 0, topMenuIdx = 0;
static const uint8_t seeableMenuRows = 3;

#define COUNT_MENU_ITEMS 3

static String mtrTest_MenuItemStr[] = {
  "forward",
  "backward",
  "fw-bw"
};

MtrMenuItem getMtr_MenuItem(){
  return (MenuItem)selectedMenuIdx;
}

void mtrMenu_StepDown(){
  if(selectedMenuIdx == COUNT_MENU_ITEMS-1){
    selectedMenuIdx = 0;
    topMenuIdx = 0;
  } else {
    selectedMenuIdx++;
    if(topMenuIdx + seeableMenuRows <= selectedMenuIdx){
      topMenuIdx++;
    }
  }
}

void mtrMenu_StepUp(){
  if(selectedMenuIdx == 0){
    selectedMenuIdx = COUNT_MENU_ITEMS-1;
    if(topMenuIdx + seeableMenuRows <= selectedMenuIdx){
      topMenuIdx = selectedMenuIdx - (seeableMenuRows - 1);
    }
  } else {
    selectedMenuIdx--;
    if(selectedMenuIdx < topMenuIdx){
      topMenuIdx--;
    }
  }
}

void showMtrMenu(){
  oled.clearDisplay();
  oled.setCursor(0,64);
  oled.setTextSize(1);
  oled.setTextColor(WHITE, BLACK);
  for(uint8_t i = 0; i < min(seeableMenuRows, COUNT_MENU_ITEMS); i++){
    oled.setCursor(i*8,64);
    uint8_t menuIdx = topMenuIdx + i;
    if(menuIdx == selectedMenuIdx){
      oled.setTextColor(BLACK, WHITE);
    } else {
      oled.setTextColor(WHITE, BLACK);
    }
    oled.println(mtrTest_MenuItemStr[menuIdx]);
  }
  oled.display();
}
*/
