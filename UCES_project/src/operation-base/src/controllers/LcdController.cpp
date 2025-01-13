#include "LcdController.h"
#include <LiquidCrystal_I2C.h>
#include "config.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setupLcd() {
  lcd.init();
  lcd.backlight();
}

void setMsg(const char* msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
}