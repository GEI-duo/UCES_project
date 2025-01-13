#include <OneButton.h>

const int BUTTON_PIN = 34;  // With external pull-down
const int LED_PIN = 27;

OneButton button(BUTTON_PIN, true);  // true -> pull-down externally

// Callback for short click
void onClick() {
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  button.attachClick(onClick);  // Triggered on short press
}

void loop() {
  button.tick();  // Continuously check button state
}
