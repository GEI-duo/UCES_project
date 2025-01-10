#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

QueueHandle_t queue1;

void sender_task(void* pvParameters);

void setup() {
  Serial.begin(115200);
  vTaskDelay(1000 / portTICK_PERIOD_MS);

  queue1 = xQueueCreate(5, sizeof(uint32_t));
  xTaskCreatePinnedToCore(sender_task, "SENDER", 1024, NULL, 4, NULL, app_cpu);
}

void loop() {
  uint32_t buffer;
  xQueueReceive(queue1, &buffer, 0);
  Serial.println(buffer);
  vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void sender_task(void* pvParameters) {
  uint32_t count = 0;
  for (;;) {
    xQueueSend(queue1, &count, 0);
    count++;
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
