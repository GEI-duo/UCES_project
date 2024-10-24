#include <ESP8266WiFi.h>
#include <Arduino.h>

#include "WifiSetup.h"

#define PIN_LED 3
#define PIN_HALL_SENSOR 2

#define LOOP_DELAY 100

bool read_hall_sensor(void);

const char *SSID = "Redmi Note 11S";
const char *PASSWORD = "0123456789";
// const char *MQTT_HOST = "";
// const int MQTT_PORT = 1234;

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_HALL_SENSOR, INPUT);

  connect_wifi(SSID, PASSWORD);
}

void loop()
{
  digitalWrite(PIN_LED, read_hall_sensor());

  delay(LOOP_DELAY);
}

bool read_hall_sensor(void)
{
  return digitalRead(PIN_HALL_SENSOR) == LOW;
}