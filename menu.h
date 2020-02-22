#ifndef MENU_H
#define MENU_H

enum MenuItem {
  Menu_battery       = 0,
  Menu_floorSen      = 1,
  Menu_oppSensors    = 2,
  Menu_tofSensors    = 3,
  Menu_gyro          = 4,
  Menu_accelerometer = 5,
  Menu_motorTest     = 6,
  Menu_fake          = 7
};

MenuItem getSelectedMenuItem();
void menu_StepDown();
void menu_StepUp();
void showMenu();

#endif /*MENU_H*/
