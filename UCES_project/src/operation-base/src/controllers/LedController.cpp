#include "LedController.h"
#include <Arduino.h>
#include "config.h"

void setupLed() {
  pinMode(LED_PIN, OUTPUT);
}

void turnOnLed() {
  digitalWrite(LED_PIN, HIGH);
}

void turnOffLed() {
  digitalWrite(LED_PIN, LOW);
}

void blinkTask(void* pvParameters) {
  while (true) {
    turnOnLed();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    turnOffLed();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

TaskHandle_t blinkTaskHandle = NULL;

void startBlinkTask() {
  xTaskCreate(blinkTask, "Blink Task", 10000, NULL, 1, &blinkTaskHandle);
}

void stopBlinkTask() {
  if (blinkTaskHandle != NULL) {
    vTaskDelete(blinkTaskHandle);
    turnOffLed();
    blinkTaskHandle = NULL;
  }
}
