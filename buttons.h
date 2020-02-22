#ifndef BUTTONS_H
#define BUTTONS_H

enum Button {
  UpButton = 0,
  DownButton = 1,
  RightButton = 2
};

enum ButtonState {
  Pressed,
  Released
};

void initButtons(void);
ButtonState getButtonState(Button button);
bool ButtonPressedEvent(Button btn);
bool DownRightEvent();
void resetButtonState();
//bool buttonsNeedUpdate();
void processButtons();

#endif /* BUTTONS_H */
