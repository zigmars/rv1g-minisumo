#include <Arduino.h>
#include "rgb_leds.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(COUNT_LED_NEO, PIN_LED_NEO, NEO_GRB + NEO_KHZ800);

void initRgbLeds(void) {
  pinMode(PIN_LED_NEO, OUTPUT);
  
}

void rgbShowIrSensorData(IrSensor_t irData) {
  for (uint8_t i = 0; i < irSensorCount; i++) {
    strip.setPixelColor(i, ((uint8_t)irData & (1 << i)) ? 10 : 0, ((uint8_t)irData & (1 << i)) ? 5 : 0, 0);
  }
  strip.show();
}

void clearRGB(void) {
  for (int i = 0; i < COUNT_LED_NEO; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();
}

/*
  typedef uint8_t[3] RgbColor;

  RgbColor colorCode[10] = {
  {  0,  0,  0},// 0
  {160,128, 96},// 1
  {255,  0,  0},// 2
  {255,160, 16},// 3
  {255,224, 32},// 4
  {  0,255,  0},// 5
  {  0,  0,255},// 6
  {160, 32,255},// 7
  {128,128,128},// 8
  {255,255,255} // 9
  };

  string colorCodeNames[10] = {
  "black",
  "brown",
  "red",
  "orange",
  "yellow",
  "green",
  "blue",
  "purple",
  "grey",
  "white",
  };

  enum ColorCodeIndex {
  BlackIndex = 0,
  BrownIndex,
  RedIndex,
  OrangeIndex,
  YellowIndex,
  GreenIndex,
  BlueIndex,
  PurpleIndex,
  GreyIndex,
  WhiteIndex,
  };
*/
