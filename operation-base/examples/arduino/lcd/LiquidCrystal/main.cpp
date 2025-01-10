#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int col = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
}

void loop() {
  lcd.clear();
  lcd.setCursor(col, 0);
  lcd.print("Welcome!");
  delay(300);  // this speeds up the simulation
  col = (col > 15 ? 0 : col + 1);
}
