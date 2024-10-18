#include <Arduino.h>

#define PIN_LED 3
#define PIN_HALL_SENSOR 2

#define LOOP_DELAY 100

bool read_hall_sensor(void);

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_HALL_SENSOR, INPUT);
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