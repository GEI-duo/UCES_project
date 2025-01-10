#include <Arduino.h>

static const int LED_PIN = 27;

void Task_1(void* pvParameters);
void Task_2(void* pvParameters);
void Task_3(void* pvParameters);

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  xTaskCreate(Task_1, "Task_1", 1000, NULL, 1, NULL);
  xTaskCreate(Task_2, "Task_2", 1000, NULL, 1, NULL);
  xTaskCreate(Task_3, "Task_3", 1000, NULL, 1, NULL);
}

void Task_1(void* pvParameters) {
  for (;;) {
    Serial.println("Task 1 is running");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void Task_2(void* pvParameters) {
  for (;;) {
    Serial.println("Task 2 is running");
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void Task_3(void* pvParameters) {
  for (;;) {
    digitalWrite(LED_PIN, HIGH);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    digitalWrite(LED_PIN, LOW);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void loop() {}