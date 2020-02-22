#include "oled.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     PIN_FLR_BACK // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire2, OLED_RESET);

void initOled(){
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while(1);
  }
//  oled.display();
//  oled.clearDisplay();
}

void oledTest(){
  
  oled.setTextSize(1);             // Normal 1:1 pixel scale
  oled.setTextColor(WHITE);        // Draw white text
  oled.setCursor(0, 0);            // Start at top-left corner
  oled.println(F("Hello, world!"));

  oled.setTextColor(BLACK, WHITE); // Draw 'inverse' text
  oled.println(3.141592);

  oled.setTextSize(2);             // Draw 2X-scale text
  oled.setTextColor(WHITE);
  oled.print(F("0x")); oled.println(0xDEADBEEF, HEX);
  
  oled.display();
  delay(1000);
  oled.clearDisplay();
}

//void showBatteryVoltage(){
//  oled.setCursor(0,64);
//  oled.setTextSize(1);
//  oled.setTextColor(WHITE, BLACK);
//  oled.println(readBatteryVoltage());
//  oled.display();
//}
