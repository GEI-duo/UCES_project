#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

const int BUTTON_PIN = 34;
const int LED_PIN = 27;

volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 200;  // 200ms debounce delay

void IRAM_ATTR toggleLED() {
  unsigned long interruptTime = millis();
  if (interruptTime - lastInterruptTime > debounceDelay) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
    lastInterruptTime = interruptTime;
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  attachInterrupt(BUTTON_PIN, toggleLED, RISING);
}

void loop() {}
