#include <Arduino.h>

#define BUTTON_PIN 34
#define LED_PIN 27

int buttonState = 0;

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    delay(10);
    if (digitalRead(BUTTON_PIN) == HIGH) {
      digitalWrite(LED_PIN, HIGH);
      if (buttonState == 0) {
        buttonState = 1;
        Serial.println("Button pressed");
      }
    } else {
      digitalWrite(LED_PIN, LOW);
      buttonState = 0;
    }
  }
}
