// https://wokwi.com/projects/385377947108184065

#include "driver/gpio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"
#include "freertos/task.h"

#define BUTTON GPIO_NUM_14  // Change GPIO if needed
#define LED GPIO_NUM_16     // Use a conflict-free GPIO

SemaphoreHandle_t sem;

void task_led(void* params) {
  gpio_set_direction(LED, GPIO_MODE_OUTPUT);  // Configure LED as output
  gpio_set_level(LED, 0);                     // Ensure LED is off initially

  uint8_t level = 0;  // Start with LED off
  for (;;) {
    xSemaphoreTake(sem, portMAX_DELAY);  // Wait for button press
    level = !level;                      // Toggle the LED state
    gpio_set_level(LED, level);          // Set the new state
  }
}

void task_button(void* params) {
  gpio_set_direction(BUTTON, GPIO_MODE_INPUT);  // Configure button as input
  gpio_pulldown_en(BUTTON);                     // Enable pull-down resistor

  for (;;) {
    if (gpio_get_level(BUTTON) == 0) {
      while (gpio_get_level(BUTTON) == 0) {
        vTaskDelay(100 / portTICK_PERIOD_MS);  // Debounce delay
      }
      xSemaphoreGive(sem);  // Signal the LED task
    }
    vTaskDelay(10 / portTICK_PERIOD_MS);  // Polling interval
  }
}

void app_main() {
  esp_log_level_set("*", ESP_LOG_INFO);
  ESP_LOGI("MAIN", "Booting...");

  sem = xSemaphoreCreateBinary();  // Create binary semaphore

  xTaskCreatePinnedToCore(task_led, "LED_TASK", 2048, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(task_button, "BUTTON_TASK", 2048, NULL, 1, NULL, 1);
}
