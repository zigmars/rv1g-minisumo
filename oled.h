#ifndef OLED_H
#define OLED_H

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

void initOled();
void oledTest();

extern Adafruit_SSD1306 oled;

//void showBatteryVoltage();

#endif /*OLED_H*/
