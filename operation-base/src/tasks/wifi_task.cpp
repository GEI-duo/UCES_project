#include <Arduino.h>
#include "managers/WifiManager.h"
#include <WiFi.h>

// Assuming mqttMutex is declared somewhere in your code
extern SemaphoreHandle_t mqttMutex;

void wifiTask(void* pvParameters) {
  while (1) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("WiFi Disconnected! Attempting reconnection...");
      WiFi.disconnect();
      wifi_connect();
    }
    vTaskDelay(pdMS_TO_TICKS(5000));  // Check every 5 seconds
  }
}