// https://wokwi.com/projects/403362123797415937  

#include "driver/ledc.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define BUZZER_PIN GPIO_NUM_18
#define BUZZER_FREQ 2000  // 2000Hz
#define BUZZER_DUTY 4000  // Duty cycle (0-8191)

void setup() {
  // Prepare and then apply the LEDC PWM timer configuration
  ledc_timer_config_t ledc_timer = {.speed_mode = LEDC_LOW_SPEED_MODE,
                                    .timer_num = LEDC_TIMER_0,
                                    .duty_resolution = LEDC_TIMER_13_BIT,
                                    .freq_hz = BUZZER_FREQ,
                                    .clk_cfg = LEDC_AUTO_CLK};
  ledc_timer_config(&ledc_timer);

  // Prepare and then apply the LEDC PWM channel configuration
  ledc_channel_config_t ledc_channel = {.speed_mode = LEDC_LOW_SPEED_MODE,
                                        .channel = LEDC_CHANNEL_0,
                                        .timer_sel = LEDC_TIMER_0,
                                        .intr_type = LEDC_INTR_DISABLE,
                                        .gpio_num = BUZZER_PIN,
                                        .duty = BUZZER_DUTY,  // Set duty to 50%
                                        .hpoint = 0};
  ledc_channel_config(&ledc_channel);
}

void app_main() {
  setup();
  // Start the PWM output
  while (1) {
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, BUZZER_DUTY);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
