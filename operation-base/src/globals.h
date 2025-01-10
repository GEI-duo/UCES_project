#pragma once

#include <PubSubClient.h>
#include <WiFi.h>
#include "managers/MqttManager.h"

extern QueueHandle_t eventQueue;

void eventQueue_init(void);