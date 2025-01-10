#include <Arduino.h>
#include <OneButton.h>
#include "config.h"

OneButton button(BUTTON_PIN, true);  // true -> pull-down externally

void setupButton(void (*clickHandler)()) {
  button.attachClick(clickHandler);
}

void loopButton() {
  button.tick();
}