#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <string>

#include "Callbacks.h"
#include "GamePlayer.h"

void reconnect(PubSubClient &client, const char *username, const char *password, int reconnect_delay, Callbacks &callbacks);
void init_mqtt_client(PubSubClient &mqtt_client, const char *mqtt_server_host, int mqtt_server_port, Callbacks &callbacks);