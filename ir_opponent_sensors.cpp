#include <Arduino.h>
#include <cstdint>
#include "ir_opponent_sensors.h"

#define IR_LED_FREQ_HZ (38000)

void initIrOpponentSensorPins(void) {
  pinMode(PIN_IR_LED, OUTPUT);

  for (uint8_t i = 0 ; i < irSensorCount; i++) {
    pinMode(irSensorPin[i], INPUT_PULLUP);
  }
}

IrSensor_t readIrSensors(void) {
  enableIrSensorTx();
  IrSensor_t sensorData = 0;
  for (uint8_t i = 0; i < irSensorCount; i++) {
    if (digitalRead(irSensorPin[i]) == LOW) {
      sensorData |= (1 << i);
    }
  }
  disableIrSensorTx();
  return sensorData;
}

void enableIrSensorTx(void) {
  tone(PIN_IR_LED, IR_LED_FREQ_HZ);
}

void disableIrSensorTx(void) {
  noTone(PIN_IR_LED);
}

#define PERIOD_IR_UPDATE 100

bool irSensorsNeedUpdate(){
  /*
        Curr   Prev  Next
          |     |     |
  . . . . . . . . . . . . . . .

  cpn ncp pnc : execute
  cnp pcn npc : not yet
check by using all three variables in unsigned form and subtracting p from n and c and seeing if c >= n, then execute
  */
  // Assure unconditional execution the first time.
  static uint32_t previousTime = 0;
  static uint32_t nextTime = 0;

  bool ret = false;
  
  uint32_t currentTime = millis();
  uint32_t c = currentTime - previousTime;
  uint32_t n = nextTime - previousTime;
  if(c > 0 && c >= n){
    previousTime = currentTime;
    nextTime = currentTime + PERIOD_IR_UPDATE;
    return true;
  }
  return false;
}
