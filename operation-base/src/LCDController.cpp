#include "LCDController.h"
#include <LiquidCrystal_I2C.h>
#include "Config.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setupLCD() {
  lcd.init();
  lcd.backlight();
}

void handleLCDMessage(const String& message) {
  lcd.clear();
  lcd.print(message);
}
