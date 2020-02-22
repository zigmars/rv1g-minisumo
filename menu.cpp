#include "oled.h"
#include "menu.h"
static uint8_t selectedMenuIdx = 0, topMenuIdx = 0;
static const uint8_t seeableMenuRows = 4;

#define COUNT_MENU_ITEMS 8

//struct MenuItem {
//  String s;
//  
//};

//#define M_ITM(A) 
//#define M_ITM(A, CUST_STR) 

static String menuItemStr[/*COUNT_MENU_ITEMS*/] = {
  "Batt",
  "Floor sen.",
  "Opp. sen.",
  "ToF sen.",
  "Gyro",
  "Accel.",
  "Mtr test",
  "Fake"
};

//void (* EnterMenu)()[/*COUNT_MENU_ITEMS*/] = {
//  .[Menu_battery] = 
//}

MenuItem getSelectedMenuItem(){
  return (MenuItem)selectedMenuIdx;
}

void menu_StepDown(){
  if(selectedMenuIdx == COUNT_MENU_ITEMS-1){
    selectedMenuIdx = 0;
    topMenuIdx = 0;
  } else {
    selectedMenuIdx++;
    if(topMenuIdx + seeableMenuRows <= selectedMenuIdx){
      topMenuIdx++;
    }
  }
}

void menu_StepUp(){
  if(selectedMenuIdx == 0){
    selectedMenuIdx = COUNT_MENU_ITEMS-1;
    if(topMenuIdx + seeableMenuRows <= selectedMenuIdx){
      topMenuIdx = selectedMenuIdx - (seeableMenuRows - 1);
    }
  } else {
    selectedMenuIdx--;
    if(selectedMenuIdx < topMenuIdx){
      topMenuIdx--;
    }
  }
}

void showMenu(){
  oled.clearDisplay();
  oled.setCursor(0,0);
  oled.setTextSize(1);
  oled.setTextColor(WHITE, BLACK);
  for(uint8_t i = 0; i < min(seeableMenuRows, COUNT_MENU_ITEMS); i++){
    uint8_t menuIdx = topMenuIdx + i;
    if(menuIdx == selectedMenuIdx){
      oled.setTextColor(BLACK, WHITE);
    } else {
      oled.setTextColor(WHITE, BLACK);
    }
    oled.println(menuItemStr[menuIdx]);
  }
  oled.display();
}
