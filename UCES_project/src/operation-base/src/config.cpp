#include <config.h>
#include <string>

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
const std::string PLAYER_ID = "duo_jc";
const std::string TOPIC_SHOOT = "players/" + PLAYER_ID + "/actions/shoot";
const std::string TOPIC_READY = "players/" + PLAYER_ID + "/actions/ready/base";
const std::string TOPIC_HAS_BULLET =
    "players/" + PLAYER_ID + "/state/has_bullet";
const std::string TOPIC_HAS_WON = "players/" + PLAYER_ID + "/state/has_won";
const std::string TOPIC_CAN_MOVE = "players/" + PLAYER_ID + "/state/can_move";
const std::string TOPIC_HAS_DIED = "players/" + PLAYER_ID + "/state/has_died";
const std::string TOPIC_STAGE = "state/stage";

// Pin definitions
const int BUTTON_PIN = 34;
const int LED_PIN = 27;
const int BUZZER_PIN = 33;
const uint8_t LCD_ADDRESS = 0x27;

// Melodies
int gameStartMelody[][2] = {
    {262, 300},  // C4
    {294, 300},  // D4
    {330, 300},  // E4
    {349, 300},  // F4
    {392, 300},  // G4
    {440, 300},  // A4
    {494, 300},  // B4
    {523, 300},  // C5
    {0, 1000}    // Rest
};

int gameWinMelody[][2] = {
    {392, 300},  // G4
    {440, 300},  // A4
    {494, 300},  // B4
    {523, 300},  // C5
    {587, 300},  // D5
    {659, 300},  // E5
    {0, 500}     // Rest
};

int gameLoseMelody[][2] = {
    {262, 300},  // C4
    {220, 300},  // A3
    {196, 300},  // G3
    {174, 300},  // F#3
    {0, 500}     // Rest
};

int gameTurnMelody[][2] = {
    {330, 200},  // E4
    {349, 200},  // F4
    {392, 200},  // G4
    {440, 200},  // A4
    {392, 200},  // G4
    {349, 200},  // F4
    {330, 200},  // E4
    {0, 500}     // Rest
};

int buttonPressMelody[][2] = {
    {440, 150},  // A4
    {523, 150},  // C5
    {587, 150},  // D5
    {659, 150},  // E5
    {0, 500}     // Rest
};