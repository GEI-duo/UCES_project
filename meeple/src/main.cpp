#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <PubSubClient.h>

#include "WifiSetup.h"
#include "MqttSetup.h"

#define PIN_HALL_SENSOR 2
#define PIN_FEEDBACK_MAGNETIC_LED 3
#define PIN_FEEDBACK_BULLET_LED 0

#define LOOP_DELAY 100
#define WIFI_RECONNECT_DELAY_MS 5000

bool read_hall_sensor(void);

const char *SSID = "POCO X5 Pro 5G";
const char *PASSWORD = "arieteariete";
const char *MQTT_HOST = "192.168.104.101";
// const char *MQTT_HOST = "test.mosquitto.org";
const int MQTT_PORT = 1883;
const char *MQTT_USERNAME = "duo_jc";
const char *MQTT_PASSWORD = "VNbxst6n";

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_FEEDBACK_MAGNETIC_LED, OUTPUT);
  pinMode(PIN_FEEDBACK_BULLET_LED, OUTPUT);
  pinMode(PIN_HALL_SENSOR, INPUT);

  connect_wifi(SSID, PASSWORD, WIFI_RECONNECT_DELAY_MS);
  init_mqtt_client(mqtt_client, MQTT_HOST, MQTT_PORT);
}

void loop()
{
  while (!mqtt_client.connected())
  {
    reconnect(mqtt_client, MQTT_USERNAME, MQTT_PASSWORD, 5000);
  }

  digitalWrite(PIN_FEEDBACK_MAGNETIC_LED, read_hall_sensor());
  digitalWrite(PIN_FEEDBACK_BULLET_LED, HIGH);

  mqtt_client.loop();

  delay(LOOP_DELAY);
}

bool read_hall_sensor(void)
{
  return digitalRead(PIN_HALL_SENSOR) == LOW;
}