#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

SemaphoreHandle_t mySemaphore;

static const int LED_PIN = 27;

void LedOnTask(void* pvParameters);
void LedOffTask(void* pvParameters);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  mySemaphore = xSemaphoreCreateCounting(1, 1);

  xTaskCreatePinnedToCore(LedOnTask, "LedOnTask", 1000, NULL, 2, NULL, app_cpu);
  xTaskCreatePinnedToCore(LedOffTask, "LedOffTask", 1000, NULL, 1, NULL,
                          app_cpu);
}

void LedOnTask(void* pvParameters) {
  for (;;) {
    if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE) {
      digitalWrite(LED_PIN, HIGH);
      Serial.println("LED is ON");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      xSemaphoreGive(mySemaphore);
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void LedOffTask(void* pvParameters) {
  for (;;) {
    if (xSemaphoreTake(mySemaphore, portMAX_DELAY) == pdTRUE) {
      digitalWrite(LED_PIN, LOW);
      Serial.println("LED is OFF");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      xSemaphoreGive(mySemaphore);
      vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void loop() {}
