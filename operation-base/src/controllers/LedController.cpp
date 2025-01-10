#include "LedController.h"
#include <Arduino.h>
#include "config.h"

void setupLed() {
  pinMode(LED_PIN, OUTPUT);
}

// void handleLedMessage(const String& message) {
//   if (message == "ON") {
//     digitalWrite(LED_PIN, HIGH);
//   } else if (message == "OFF") {
//     digitalWrite(LED_PIN, LOW);
//   }
// }
