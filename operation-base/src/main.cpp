#include <Arduino.h>
#include <OneButton.h>
#include <WiFi.h>
#include "config.h"
#include "controllers/ButtonController.h"
#include "controllers/LcdController.h"
#include "events.h"
#include "globals.h"
#include "managers/MqttManager.h"
#include "managers/WifiManager.h"
#include "tasks/button_task.h"
#include "tasks/game_loop_task.h"
#include "tasks/mqtt_task.h"
#include "tasks/wifi_task.h"

void onClickHandler() {
  Event event;
  event.type = EVENT_BUTTON_PRESS;
  event.data = NULL;

  xQueueSend(eventQueue, &event, portMAX_DELAY);
}

void setup() {
  Serial.begin(115200);

  wifi_init();
  mqtt_init();

  setupButton(onClickHandler);
  setupLcd();
  eventQueue_init();

  xTaskCreate(wifiTask, "WiFi Task", 10000, NULL, 1, NULL);
  xTaskCreate(mqttTask, "MQTT Task", 10000, NULL, 1, NULL);
  xTaskCreate(buttonTask, "Button Task", 10000, NULL, 1, NULL);
  xTaskCreate(gameLoopTask, "Game Task", 10000, NULL, 1, NULL);
}

void loop() {}
