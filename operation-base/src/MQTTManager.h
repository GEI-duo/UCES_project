#pragma once
#ifndef MQTTMANAGER_H
#define MQTTMANAGER_H

#include <PubSubClient.h>
#include <WiFi.h>

class MQTTManager {
 public:
  MQTTManager(WiFiClient& wifiClient, PubSubClient& mqttClient)
      : wifiClient(wifiClient), mqttClient(mqttClient) {}

  void connect();

 private:
  WiFiClient& wifiClient;
  PubSubClient& mqttClient;
};

void setupMQTT(PubSubClient& client);
void reconnectMQTT(PubSubClient& client);
void mqttCallback(char* topic, byte* payload, unsigned int length);

#endif
