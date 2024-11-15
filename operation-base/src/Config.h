#pragma once
#ifndef CONFIG_H
#define CONFIG_H

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
#define BUTTON_PIN 34
#define LED_PIN 27
#define BUZZER_PIN 33
#define LCD_ADDRESS 0x27

#endif
