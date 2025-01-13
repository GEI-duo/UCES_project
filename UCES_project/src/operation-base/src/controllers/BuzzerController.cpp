#include "BuzzerController.h"
#include <Arduino.h>
#include "config.h"

void setupBuzzer() {
  pinMode(BUZZER_PIN, OUTPUT);
}

struct MelodyData {
  int (*melody)[2];
  int size;
};

void playMelodyTask(void* pvParameters) {
  MelodyData* data = (MelodyData*)pvParameters;
  int(*melody)[2] = data->melody;
  int size = data->size;

  for (int i = 0; i < size; i++) {
    int note = melody[i][0];
    int duration = melody[i][1];
    if (note == 0) {
      vTaskDelay(duration / portTICK_PERIOD_MS);
    } else {
      tone(BUZZER_PIN, note, duration);
      vTaskDelay(20 / portTICK_PERIOD_MS);
    }
  }

  // Delete the task once done
  vTaskDelete(NULL);
}
