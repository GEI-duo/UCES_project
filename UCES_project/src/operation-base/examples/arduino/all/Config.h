#pragma once
#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>

// WiFi credentials
extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;

// MQTT server configuration
extern const char* MQTT_SERVER;
extern const int MQTT_PORT;
extern const char* MQTT_USER;
extern const char* MQTT_PASSWORD;

// MQTT topics
extern const char* TOPIC_LED;
extern const char* TOPIC_BUZZER;
extern const char* TOPIC_LCD;
extern const char* TOPIC_BUTTON;

// Pin definitions
extern const int BUTTON_PIN;
extern const int LED_PIN;
extern const int BUZZER_PIN;
extern const uint8_t LCD_ADDRESS;

#endif
