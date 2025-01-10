#include "BuzzerController.h"
#include <Arduino.h>
#include "Config.h"

void setupBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void handleBuzzerMessage(const String& message) {
  if (message == "PLAY") {
    tone(BUZZER_PIN, 1000, 500);  // Play tone at 1000 Hz for 500 ms
  } else if (message == "STOP") {
    noTone(BUZZER_PIN);
  }
}
