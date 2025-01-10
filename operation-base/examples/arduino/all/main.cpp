#include <Arduino.h>
#include <WiFi.h>
#include "ButtonController.h"
#include "BuzzerController.h"
#include "Config.h"
#include "LCDController.h"
#include "LEDController.h"
#include "MQTTManager.h"
#include "WiFiManager.h"

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);
MQTTManager mqttManager(wifiClient, mqttClient);

void setup() {
  Serial.begin(115200);

  setupWiFi();
  setupMQTT(mqttClient);
  setupLED();
  setupBuzzer();
  setupLCD();
  setupButton();
}

void loop() {
  if (!mqttClient.connected()) {
    reconnectMQTT(mqttClient);
  }
  mqttClient.loop();
  checkButtonPress(mqttClient);
}
