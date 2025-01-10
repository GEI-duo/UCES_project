#include <HD44780.h>
#include <driver/i2c.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include "sdkconfig.h"

// #define LCD_ADDR 0x27
#define LCD_ADDR 0x4E >> 1
#define SDA_PIN 21
#define SCL_PIN 22
#define LCD_COLS 16
#define LCD_ROWS 2

void LCD_DemoTask(void* param) {
  char num[20];
  while (true) {
    LCD_home();
    LCD_clearScreen();
    LCD_writeStr("16x2 I2C LCD");
    vTaskDelay(pdMS_TO_TICKS(3000));
    LCD_clearScreen();
    LCD_writeStr("Lets Count 0-10!");
    vTaskDelay(pdMS_TO_TICKS(3000));
    LCD_clearScreen();
    for (int i = 0; i <= 10; i++) {
      LCD_setCursor(8, 2);
      sprintf(num, "%d", i);
      LCD_writeStr(num);
      vTaskDelay(pdMS_TO_TICKS(1000));
    }
  }
}

void app_main(void) {
  LCD_init(LCD_ADDR, SDA_PIN, SCL_PIN, LCD_COLS, LCD_ROWS);
  xTaskCreate(&LCD_DemoTask, "Demo Task", 2048, NULL, 5, NULL);
}
