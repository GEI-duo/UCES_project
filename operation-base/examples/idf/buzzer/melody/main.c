#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUZZER_PIN GPIO_NUM_18
#define LEDC_CHANNEL LEDC_CHANNEL_0
#define LEDC_TIMER LEDC_TIMER_0
#define BUZZER_DUTY 4000  // 50% duty cycle (0-8191)

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
void play_melody() {
  int melody[][2] = {
      {262, 500},  // C4, 500ms
      {294, 500},  // D4, 500ms
      {330, 500},  // E4, 500ms
      {349, 500},  // F4, 500ms
      {392, 500},  // G4, 500ms
      {440, 500},  // A4, 500ms
      {494, 500},  // B4, 500ms
      {523, 500},  // C5, 500ms
  };

  for (int i = 0; i < 8; i++) {
    play_tone(melody[i][0], melody[i][1]);
    vTaskDelay(100 / portTICK_PERIOD_MS);  // Small delay between notes
  }
}

void app_main() {
  setup_buzzer();
  while (1) {
    play_melody();                          // Play the melody
    vTaskDelay(5000 / portTICK_PERIOD_MS);  // Wait before replaying
  }
}
