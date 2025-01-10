#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const uint8_t msg_queue_len = 5;
static QueueHandle_t msg_queue;

static const int LED_PIN = 27;

void print_msg(void* parameter) {
  uint8_t tmp_item;

  while (1) {
    // See if there's a message in the queue (do not block)
    if (xQueueReceive(msg_queue, (void*)&tmp_item, 0) == pdTRUE) {
      Serial.println(tmp_item);
    }

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  msg_queue = xQueueCreate(msg_queue_len, sizeof(uint8_t));

  if (msg_queue == NULL) {
    Serial.println("[Err] Can\'t create queue");
  }

  xTaskCreatePinnedToCore(print_msg, "print_msg0", 1024, NULL, 1, NULL,
                          app_cpu);
}

void loop() {
  static int num = 0;

  if (xQueueSend(msg_queue, (void*)&num, 10) != pdTRUE) {
    Serial.println("[Err] Queue full!");
  }

  num++;
  vTaskDelay(500 / portTICK_PERIOD_MS);
}