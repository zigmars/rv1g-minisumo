#ifndef UTILS_H
#define UTILS_H

#include <cstdint>

void swap(uint8_t &a, uint8_t &b);
void hardwareTest(void);

static void showCalTitle();
void calibrateBattAdcOffset();

float readVoltage(int pin);
float readBatteryVoltage(void);

#endif /* UTILS_H */
