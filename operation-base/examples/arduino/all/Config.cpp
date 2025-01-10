#include <Config.h>

// WiFi credentials
const char* WIFI_SSID = "MIWIFI_2G_aYUz";
const char* WIFI_PASSWORD = "0123456789j";

// MQTT server configuration
const char* MQTT_SERVER = "192.168.1.138";
const int MQTT_PORT = 1883;
const char* MQTT_USER = "meeple_jc";
const char* MQTT_PASSWORD = "VNbxst6n";

// MQTT topics
const char* TOPIC_LED = "home/led";
const char* TOPIC_BUZZER = "home/buzzer";
const char* TOPIC_LCD = "home/lcd";
const char* TOPIC_BUTTON = "home/button";

// Pin definitions
const int BUTTON_PIN = 34;
const int LED_PIN = 27;
const int BUZZER_PIN = 33;
const uint8_t LCD_ADDRESS = 0x27;