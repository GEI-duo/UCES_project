#pragma once

#include <PubSubClient.h>
#include <WiFi.h>

extern WiFiClient espClient;
extern PubSubClient client;

void mqttInit();
void mqttReconnect();
void mqttCallback(char* topic, byte* payload, unsigned int length);
void mqttPublish(const char* topic, const char* message);
void mqttTask(void* pvParameters);