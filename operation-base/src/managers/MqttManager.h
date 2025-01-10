#pragma once

#include <PubSubClient.h>
#include <WiFi.h>

extern WiFiClient espClient;
extern PubSubClient client;

void mqtt_init();
void mqtt_reconnect();
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void mqtt_publish(const char* topic, const char* message);