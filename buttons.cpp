#include <Arduino.h>
#include <cstdint>
#include "buttons.h"


#define COUNT_BUTTONS 3
static const uint8_t buttonPins[COUNT_BUTTONS] = {PIN_BUTTON1, PIN_BUTTON2, PIN_BUTTON3};
static ButtonState _buttonState[COUNT_BUTTONS];

void initButtons(void) {
  for (uint8_t i = 0; i < COUNT_BUTTONS; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
}

ButtonState getButtonState(Button button) {
  uint8_t buttonIdx = (uint8_t)button;
  return (digitalRead(buttonPins[buttonIdx]) == LOW) ? Pressed : Released;
}

static ButtonState getOldState(Button btn){
  return _buttonState[(uint8_t)btn];
}

static void updateOldState(Button btn, ButtonState state){
  _buttonState[(uint8_t)btn] = state;
}


#define PERIOD_BUTTON_UPDATE 20
static uint32_t previousTime[COUNT_BUTTONS] = {0};
static uint32_t nextTime[COUNT_BUTTONS] = {0};

static bool buttonNeedsUpdate(Button btn){
  bool ret = false;
  
  uint32_t currentTime = millis();
  uint32_t c = currentTime - previousTime[(uint8_t)btn];
  uint32_t n = nextTime[(uint8_t)btn] - previousTime[(uint8_t)btn];
  if(c > 0 && c >= n){
    previousTime[(uint8_t)btn] = currentTime;
    nextTime[(uint8_t)btn] = currentTime + PERIOD_BUTTON_UPDATE;
    return true;
  }
  return false;
}

bool ButtonPressedEvent(Button btn){
  /* Achieves software debounce */
  if(!buttonNeedsUpdate(btn)){
    return false;
  }
  bool ret = false;
  ButtonState newState = getButtonState(btn);
  ret = (getOldState(btn) == Released && newState == Pressed);
  updateOldState(btn, newState);
  return ret;
}

bool DownRightEvent(){
  return getButtonState(DownButton) == Pressed && ButtonPressedEvent(RightButton);
}

void resetButtonState(){
  for (uint8_t i = 0; i < COUNT_BUTTONS; i++) {
    _buttonState[i] = getButtonState((Button)i);
  }
}

void processButtons(){
  
}
