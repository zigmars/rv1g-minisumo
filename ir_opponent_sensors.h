#ifndef IR_OPPONENT_SENSORS_H
#define IR_OPPONENT_SENSORS_H

#include <Arduino.h>
#include <cstdint>

const uint8_t irSensorPin[] = {PIN_IR_SENSOR1, PIN_IR_SENSOR2, PIN_IR_SENSOR3, PIN_IR_SENSOR4, PIN_IR_SENSOR5};
const uint8_t irSensorCount = 5;//size(irSensorPin);

typedef uint8_t IrSensor_t;

void initIrOpponentSensorPins(void);
IrSensor_t readIrSensors(void);
void enableIrSensorTx(void);
void disableIrSensorTx(void);
bool irSensorsNeedUpdate();
#endif /* IR_OPPONENT_SENSORS_H */
