#include "tasks/mqtt_task.h"
#include "globals.h"
#include "managers/MqttManager.h"

void mqttTask(void* pvParameters) {
  while (1) {
    if (!client.connected()) {
      mqtt_reconnect();
    }
    client.loop();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}