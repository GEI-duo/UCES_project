#pragma once

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <PubSubClient.h>

#include "WifiSetup.h"
#include "MqttSetup.h"
#include "Callbacks.h"
#include "GamePlayer.h"

#define PIN_HALL_SENSOR 2
#define PIN_FEEDBACK_MAGNETIC_LED 3
#define PIN_FEEDBACK_BULLET_LED 1 // IMPORTANT: Use 1 for playing 0 for debugging

#define LOOP_DELAY 0
#define WIFI_RECONNECT_DELAY_MS 1000

const char *SSID = "spinel";
const char *PASSWORD = "arieteariete";

const char *MQTT_HOST = "agrospai.udl.cat";
// const char *MQTT_HOST = "test.mosquitto.org";
const int MQTT_PORT = 1883;
const char *MQTT_USERNAME = "duo_jc";
const char *MQTT_PASSWORD = "VNbxst6n";