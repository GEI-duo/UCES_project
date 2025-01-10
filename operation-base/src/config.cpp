#include <config.h>

// WiFi credentials
// const char* WIFI_SSID = "jordigv-net";
// const char* WIFI_PASSWORD = "0123456789";
const char* WIFI_SSID = "MIWIFI_2G_aYUz";
const char* WIFI_PASSWORD = "0123456789j";

// MQTT server configuration
const char* MQTT_SERVER = "agrospai.udl.cat";
const int MQTT_PORT = 1883;
const char* MQTT_USER = "duo_jc";
const char* MQTT_PASSWORD = "VNbxst6n";

// MQTT topics
const char* PLAYER_ID = "duo_jc";
const char* TOPIC_SHOOT = "players/duo_jc/actions/shoot";
const char* TOPIC_READY = "players/duo_jc/actions/ready/base";
const char* TOPIC_HAS_BULLET = "players/duo_jc/state/has_bullet";
const char* TOPIC_HAS_WON = "players/duo_jc/state/has_won";
const char* TOPIC_CAN_MOVE = "players/duo_jc/state/can_move";
const char* TOPIC_HAS_DIED = "players/duo_jc/state/has_died";
const char* TOPIC_STAGE = "state/stage";

// Pin definitions
const int BUTTON_PIN = 34;
const int LED_PIN = 27;
const int BUZZER_PIN = 33;
const uint8_t LCD_ADDRESS = 0x27;