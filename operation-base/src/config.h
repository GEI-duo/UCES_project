#pragma once

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
extern const char* TOPIC_SHOOT;
extern const char* TOPIC_READY;
extern const char* TOPIC_HAS_BULLET;
extern const char* TOPIC_HAS_WON;
extern const char* TOPIC_CAN_MOVE;
extern const char* TOPIC_HAS_DIED;
extern const char* TOPIC_STAGE;

// Pin definitions
extern const int BUTTON_PIN;
extern const int LED_PIN;
extern const int BUZZER_PIN;
extern const uint8_t LCD_ADDRESS;
