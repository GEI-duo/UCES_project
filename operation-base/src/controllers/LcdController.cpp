#include "LcdController.h"
#include <LiquidCrystal_I2C.h>
#include "config.h"

LiquidCrystal_I2C lcd(LCD_ADDRESS, 16, 2);

void setupLcd() {
  lcd.init();
  lcd.backlight();
}

void setRows(const char* firstRow, const char* secondRow) {
  lcd.clear();

  // Define the maximum length of a single line on the display
  const int maxLineLength = 16;

  // Truncate or wrap the first line if it exceeds the max length
  char firstRowToShow[maxLineLength + 1]; // +1 for the null terminator
  strncpy(firstRowToShow, firstRow, maxLineLength);
  firstRowToShow[maxLineLength] = '\0';  // Ensure the string is null-terminated
  lcd.setCursor(0, 0);
  lcd.print(firstRowToShow);

  // Truncate or wrap the second line if it exceeds the max length
  char secondLineToShow[maxLineLength + 1]; // +1 for the null terminator
  strncpy(secondLineToShow, secondRow, maxLineLength);
  secondLineToShow[maxLineLength] = '\0';  // Ensure the string is null-terminated
  lcd.setCursor(0, 1);
  lcd.print(secondLineToShow);
}
