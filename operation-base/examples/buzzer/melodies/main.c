#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "melody.h"
#include "pitches.h"

#define BUZZER_PIN GPIO_NUM_18
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_0
#define BUZZER_DUTY 4000  // 50% duty cycle (0-8191)

int gameStartMelody[][2] = {
    {262, 300},  // C4
    {294, 300},  // D4
    {330, 300},  // E4
    {349, 300},  // F4
    {392, 300},  // G4
    {440, 300},  // A4
    {494, 300},  // B4
    {523, 300},  // C5
    {0, 1000}    // Rest
};

int gameWinMelody[][2] = {
    {392, 300},  // G4
    {440, 300},  // A4
    {494, 300},  // B4
    {523, 300},  // C5
    {587, 300},  // D5
    {659, 300},  // E5
    {0, 500}     // Rest
};

int gameLoseMelody[][2] = {
    {262, 300},  // C4
    {220, 300},  // A3
    {196, 300},  // G3
    {174, 300},  // F#3
    {0, 500}     // Rest
};

int gameTurnMelody[][2] = {
    {330, 200},  // E4
    {349, 200},  // F4
    {392, 200},  // G4
    {440, 200},  // A4
    {392, 200},  // G4
    {349, 200},  // F4
    {330, 200},  // E4
    {0, 500}     // Rest
};

int buttonPressMelody[][2] = {
    {440, 150},  // A4
    {523, 150},  // C5
    {587, 150},  // D5
    {659, 150},  // E5
    {0, 500}     // Rest
};

// Initialize the LEDC timer and channel
void setup_buzzer() {
  ledc_timer_config_t ledc_timer = {.speed_mode = LEDC_LOW_SPEED_MODE,
                                    .timer_num = LEDC_TIMER,
                                    .duty_resolution = LEDC_TIMER_13_BIT,
                                    .freq_hz = 1000,  // Default frequency
                                    .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&ledc_timer);

  ledc_channel_config_t ledc_channel = {
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL,
      .timer_sel = LEDC_TIMER,
      .intr_type = LEDC_INTR_DISABLE,
      .gpio_num = BUZZER_PIN,
      .duty = 0,  // Start with duty cycle 0 (buzzer off)
      .hpoint = 0};
  ledc_channel_config(&ledc_channel);
}

// Tone function: Set frequency and play for a duration
void play_tone(int frequency, int duration_ms) {
  // Set the frequency
  ledc_set_freq(LEDC_LOW_SPEED_MODE, LEDC_TIMER, frequency);
  // Set the duty cycle (turn on the buzzer)
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL, BUZZER_DUTY);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL);

  // Wait for the specified duration
  vTaskDelay(duration_ms / portTICK_PERIOD_MS);

  // Stop the buzzer
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL, 0);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL);
}

// Melody player: Plays a sequence of notes
void play_melody(int melody[][2], int size) {
  for (int i = 0; i < size; i++) {
    int note = melody[i][0];
    int duration = melody[i][1];
    if (note == 0) {
      // Rest
      vTaskDelay(duration / portTICK_PERIOD_MS);
    } else {
      // Play the note
      play_tone(note, duration);
      // Delay between notes
      vTaskDelay(20 / portTICK_PERIOD_MS);
    }
  }
}

void play_melodies() {
  play_melody(gameStartMelody,
              sizeof(gameStartMelody) / sizeof(gameStartMelody[0]));
  play_melody(gameWinMelody, sizeof(gameWinMelody) / sizeof(gameWinMelody[0]));
  play_melody(gameLoseMelody,
              sizeof(gameLoseMelody) / sizeof(gameLoseMelody[0]));
  play_melody(gameTurnMelody,
              sizeof(gameTurnMelody) / sizeof(gameTurnMelody[0]));
  play_melody(buttonPressMelody,
              sizeof(buttonPressMelody) / sizeof(buttonPressMelody[0]));
}

void app_main() {
  setup_buzzer();
  while (1) {
    play_melodies();                        // Play the melodies
    vTaskDelay(5000 / portTICK_PERIOD_MS);  // Wait before replaying
  }
}
