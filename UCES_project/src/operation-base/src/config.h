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
const std::string TOPIC_SHOOT;
const std::string TOPIC_READY;
const std::string TOPIC_HAS_BULLET;
const std::string TOPIC_HAS_WON;
const std::string TOPIC_CAN_MOVE;
const std::string TOPIC_HAS_DIED;
const std::string TOPIC_STAGE;

// Pin definitions
extern const int BUTTON_PIN;
extern const int LED_PIN;
extern const int BUZZER_PIN;
extern const uint8_t LCD_ADDRESS;

// Melodies
extern int gameStartMelody[][2];
extern int gameWinMelody[][2];
extern int gameLoseMelody[][2];
extern int gameTurnMelody[][2];
extern int gameShootMelody[][2];