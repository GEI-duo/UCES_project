#include "ButtonController.h"
#include <Arduino.h>
#include "Config.h"

void setupButton(PubSubClient& client) {
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);
}

void checkButtonPress(PubSubClient& client) {
  static unsigned long lastPressTime = 0;
  static bool lastButtonState = HIGH;  // Track previous state of the button

  unsigned long currentTime = millis();
  bool currentButtonState =
      digitalRead(BUTTON_PIN);  // Read current state of the button

  // Check for button press (LOW to HIGH transition)
  if (currentButtonState == LOW && lastButtonState == HIGH) {
    // Check if enough time has passed since the last button press
    if (currentTime - lastPressTime > 1000) {  // 1 second debounce delay
      client.publish(TOPIC_BUTTON, "Button pressed");
      lastPressTime = currentTime;  // Update last press time
    }
  }

  // Update button state for the next iteration
  lastButtonState = currentButtonState;
}