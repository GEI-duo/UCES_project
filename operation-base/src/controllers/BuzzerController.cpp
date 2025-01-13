#include "BuzzerController.h"
#include <Arduino.h>
#include "config.h"

void setupBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void playMelodyTask(void* pvParameters) {
  // Cast pvParameters to a Melody pointer
  Melody* melodyData = (Melody*)pvParameters;

  Serial.println("Playing melody...");
  for (int i = 0; i < melodyData->size; i++) {
    int note = melodyData->notes[i][0];
    int duration = melodyData->notes[i][1];
    if (note == 0) {
      vTaskDelay(duration / portTICK_PERIOD_MS);  // Silence
    } else {
      tone(BUZZER_PIN, note, duration);          // Play note
      vTaskDelay(duration / portTICK_PERIOD_MS);
    }
  }

  // Delete the task once done
  vTaskDelete(NULL);
}

void playMelody(const Melody& melody) {
  xTaskCreate(playMelodyTask, "Play Melody Task", 1024, (void*)&melody, 1, NULL);
}