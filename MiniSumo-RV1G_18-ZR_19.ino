#include "utils.h"
#include "buttons.h"
#include "ir_opponent_sensors.h"
#include "motors.h"
#include "rgb_leds.h"
#include "oled.h"
#include "menu.h"

/**
   Mini Sumo available defines:
     PIN_FLR_LEFT, PIN_FLR_RIGHT, PIN_FLR_BACK
     PIN_ADC_BAT
     PIN_IR_SENSOR1, PIN_IR_SENSOR2, PIN_IR_SENSOR3, PIN_IR_SENSOR4, PIN_IR_SENSOR5
     PIN_IR_LED
     PIN_LED_RED, PIN_LED_GREEN
     PIN_MOTOR1_1, PIN_MOTOR2_2, PIN_MOTOR1_2, PIN_MOTOR2_1
     PIN_BUTTON1, PIN_BUTTON2, PIN_BUTTON3
     PIN_LASER_1_RST, PIN_LASER_2_RST, PIN_LASER_3_RST
     PIN_LED_NEO
     COUNT_LED_NEO
     PIN_BUZZER
**/

void setup() {
  initButtons();
  initIrOpponentSensorPins();
  initRgbLeds();
  initOled();
  //  initFloorSensors();
  hardwareTest();
  Serial.begin(115200);

  analogReadResolution(ADC_RESOLUTION);
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_GREEN, OUTPUT);

  digitalWrite(PIN_LED_RED, HIGH);
  digitalWrite(PIN_LED_GREEN, LOW);

  //  calibrateBattAdcOffset();
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_GREEN, HIGH);

  showMenu();
}

void loop() {

  if (irSensorsNeedUpdate()) {
    digitalWrite(PIN_LED_GREEN, LOW);
    IrSensor_t irData = readIrSensors();
    rgbShowIrSensorData(irData);
    digitalWrite(PIN_LED_GREEN, HIGH);
  }
  bool updateMenu = false;
  if (ButtonPressedEvent(RightButton)) {
    while (!DownRightEvent()) {
      switch (getSelectedMenuItem()) {
        case Menu_battery:
          __asm__ __volatile__("");
          break;
        case Menu_floorSen:
          __asm__ __volatile__("");
          break;
        case Menu_oppSensors:
          __asm__ __volatile__("");
          break;
        case Menu_tofSensors:
          __asm__ __volatile__("");
          break;
        case Menu_gyro:
          __asm__ __volatile__("");
          break;
        case Menu_accelerometer:
          __asm__ __volatile__("");
          break;
        case Menu_motorTest:
          __asm__ __volatile__("");
          break;
        case Menu_fake:
          __asm__ __volatile__("");
          break;
      }
    }
    resetButtonState();
    updateMenu = true;
  }
  
  if (ButtonPressedEvent(DownButton)) {
    menu_StepDown();
    updateMenu = true;
  }
  if (ButtonPressedEvent(UpButton)) {
    menu_StepUp();
    updateMenu = true;
  }
  if (updateMenu) {
    showMenu();
  }
}
