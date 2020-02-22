#ifndef MOTORS_H
#define MOTORS_H

#define PIN_MTR_LEFT_1 PIN_MOTOR1_1
#define PIN_MTR_LEFT_2 PIN_MOTOR1_2
#define PIN_MTR_RIGHT_1 PIN_MOTOR2_1
#define PIN_MTR_RIGHT_2 PIN_MOTOR2_2

const uint8_t mtrPins[] = {PIN_MOTOR1_1, PIN_MOTOR1_2, PIN_MOTOR2_1, PIN_MOTOR2_2};

struct Motor {
  Motor(uint8_t p1, uint8_t p2) : pin1(p1), pin2(p2) {};
  uint8_t pin1, pin2;
};

const Motor leftMotor(PIN_MTR_LEFT_1, PIN_MTR_LEFT_2);
const Motor rightMotor(PIN_MTR_RIGHT_1, PIN_MTR_RIGHT_2);

enum DecayMode { // internal value corresponds to the fixed pin level
  FastDecay = 0,
  SlowDecay = 1
};

#define CoastMode FastDecay
#define BreakMode SlowDecay

enum MotorDirection {
  Forward = 0,
  Backward = 1
};

void MotorPwmDrive(Motor mtr, DecayMode decay, MotorDirection dir, uint8_t power);

/*enum MtrMenuItem {
  Forward,
  Backward,
  Forward_Backward
};

MtrMenuItem getMtr_MenuItem();
void mtrMenu_StepDown();
void mtrMenu_StepUp();
void showMtrMenu();
*/

#endif /* MOTORS_H */
