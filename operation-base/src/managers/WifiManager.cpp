#include <WiFi.h>
#include "config.h"

void wifi_connect() {
  Serial.print("Connecting to WiFi...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(500 / portTICK_PERIOD_MS);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi!");
}

void wifi_init() {
  WiFi.mode(WIFI_STA);
  wifi_connect();
}