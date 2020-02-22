#ifndef RGB_LEDS_H
#define RGB_LEDS_H

#include <cstdint>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "ir_opponent_sensors.h"

extern Adafruit_NeoPixel strip;

void initRgbLeds(void);
void rgbShowIrSensorData(IrSensor_t irData);
void clearRGB(void);

#endif /* RGB_LEDS_H */
