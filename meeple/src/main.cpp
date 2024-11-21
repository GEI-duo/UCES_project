#include "main.h"

int read_hall_sensor(void);

void write_feedback(const ulong);
void read_feedback(const ulong);

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);
Player player(MQTT_USERNAME, mqtt_client);
Callbacks cb(player);

const u16_t green_interval = 500; // Blinking interval for the green LED
ulong green_time = 0;             // Time when the green LED was turned on

int hall_sensor = LOW;

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
  ulong t = millis();

  while (!mqtt_client.connected())
  {
    connect(mqtt_client, MQTT_USERNAME, MQTT_PASSWORD, 5000, cb);
    player.publish_ready();
  }

  read_feedback(t);
  write_feedback(t);

  mqtt_client.loop();

  delay(LOOP_DELAY);
}

int read_hall_sensor(void)
{
  return digitalRead(PIN_HALL_SENSOR) == LOW ? HIGH : LOW;
}

void read_feedback(const ulong t)
{
  const bool last_hall_sensor = hall_sensor;

  // if (player.state != WALKING || player.state != SHOOTING)
  //   return;

  hall_sensor = read_hall_sensor();

  const bool is_hall_sensor_changed = last_hall_sensor != hall_sensor;

  Serial.printf("Hall sensor changed? %d\n", is_hall_sensor_changed);

  if (is_hall_sensor_changed)
  {
    if (hall_sensor == HIGH)
    {
      player.publish_moved();
    }
    else
    {
      player.publish_died();
    }
  }
}

void write_feedback(const ulong t)
{
  // GREEN LED (Moving)
  if (player.can_move())
  {
    Serial.println("CAN MOVE: green LED animation!");
    if (t > green_time)
    {
      digitalWrite(PIN_FEEDBACK_MAGNETIC_LED, hall_sensor);
      green_time = t + green_interval;
    }
    else
    {
      digitalWrite(PIN_FEEDBACK_MAGNETIC_LED, LOW);
    }
  }
  else
  {
    // GREEN LED if hall sensor
    digitalWrite(PIN_FEEDBACK_MAGNETIC_LED, hall_sensor);
  }

  // YELLOW LED (Bullet)
  digitalWrite(PIN_FEEDBACK_BULLET_LED, player.has_bullet() ? HIGH : LOW);
}