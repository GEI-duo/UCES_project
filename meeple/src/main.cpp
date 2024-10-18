#include <Arduino.h>

#define PIN_LED 3
#define PIN_HALL_SENSOR 5

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_HALL_SENSOR, INPUT);
}

void loop()
{
  digitalWrite(PIN_LED, HIGH);
  delay(1000);

  Serial.write("Lights out!");

  digitalWrite(PIN_LED, LOW);
  delay(1000);
}
