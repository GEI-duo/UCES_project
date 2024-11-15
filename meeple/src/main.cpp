#include "main.h"

bool read_hall_sensor(void);

void write_feedback(void);
void read_feedback(void);

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);
Player player(MQTT_USERNAME, mqtt_client);
Callbacks cb(player);

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_FEEDBACK_MAGNETIC_LED, OUTPUT);
  pinMode(PIN_FEEDBACK_BULLET_LED, OUTPUT);
  pinMode(PIN_HALL_SENSOR, INPUT);

  connect_wifi(SSID, PASSWORD, WIFI_RECONNECT_DELAY_MS);
  init_mqtt_client(mqtt_client, MQTT_HOST, MQTT_PORT, cb);
}

void loop()
{
  while (!mqtt_client.connected())
  {
    reconnect(mqtt_client, MQTT_USERNAME, MQTT_PASSWORD, 5000, cb);

    // Publish ready message
    player.publish_ready();
  }

  read_feedback();
  write_feedback();

  mqtt_client.loop();

  delay(LOOP_DELAY);
}

bool read_hall_sensor(void)
{
  return digitalRead(PIN_HALL_SENSOR) == LOW;
}

void read_feedback(void)
{
}

void write_feedback(void)
{
  digitalWrite(PIN_FEEDBACK_MAGNETIC_LED, read_hall_sensor());
  digitalWrite(PIN_FEEDBACK_BULLET_LED, HIGH);
}