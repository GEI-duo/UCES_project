#include "LEDController.h"
#include "Config.h"

void  setupLED() {
  pinMode(LED_PIN, OUTPUT);
}

void handleLEDMessage(const String& message) {
  if (message == "ON") {
    digitalWrite(LED_PIN, HIGH);
  } else if (message == "OFF") {
    digitalWrite(LED_PIN, LOW);
  }
}
