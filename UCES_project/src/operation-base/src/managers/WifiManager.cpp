#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

void wifiConnect() {
  Serial.print("Connecting to WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(500 / portTICK_PERIOD_MS);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void wifiInit() {
  WiFi.mode(WIFI_STA);
  wifiConnect();
}

extern SemaphoreHandle_t mqttMutex;

void wifiTask(void* pvParameters) {
  while (1) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi Disconnected! Attempting reconnection...");
      WiFi.disconnect();
      wifiConnect();
    }
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}