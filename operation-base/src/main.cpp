#include <Arduino.h>
#include <WiFi.h>
#include "config.h"
#include "controllers/ButtonController.h"
#include "controllers/BuzzerController.h"
#include "controllers/LcdController.h"
#include "controllers/LedController.h"
#include "events.h"
#include "globals.h"
#include "managers/GameManager.h"
#include "managers/MqttManager.h"
#include "managers/WifiManager.h"

void onClickHandler() {
  Event event;
  event.type = EVENT_BUTTON_PRESS;
  event.data = NULL;

  xQueueSend(eventQueue, &event, portMAX_DELAY);
}

void setup() {
  Serial.begin(115200);

  wifiInit();
  mqttInit();

  setupButton(onClickHandler);
  setupLcd();
  setupLed();
  setupBuzzer();
  eventQueue_init();

  setRows("Meeple Showdown!", "Press to join...");
  turnOnLed();
  playMelody(gameStartMelody);

  xTaskCreate(wifiTask, "WiFi Task", 10000, NULL, 1, NULL);
  xTaskCreate(mqttTask, "MQTT Task", 10000, NULL, 1, NULL);
  xTaskCreate(buttonTask, "Button Task", 10000, NULL, 1, NULL);
  xTaskCreate(gameLoopTask, "Game Task", 10000, NULL, 1, NULL);
}

void loop() {}
