#include <string.h>
#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Use UART0 (connected to USB)
#define UART_PORT UART_NUM_0  // UART0 is connected to the USB
#define BUF_SIZE (1024)       // Buffer size for UART

void uart_init() {
  // Configure UART parameters
  uart_config_t uart_config = {
      .baud_rate = 115200,
      .data_bits = UART_DATA_8_BITS,
      .parity = UART_PARITY_DISABLE,
      .stop_bits = UART_STOP_BITS_1,
      .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
  };

  // Initialize UART driver
  uart_param_config(UART_PORT, &uart_config);
  uart_driver_install(UART_PORT, BUF_SIZE, 0, 0, NULL, 0);
}

void hello_world_task(void* pvParameters) {
  const char* msg = "Hello, World!\n";

  while (true) {
    // Send message over UART0 (USB)
    uart_write_bytes(UART_PORT, msg, strlen(msg));
    vTaskDelay(pdMS_TO_TICKS(1000));  // Delay 1 second
  }
}

void app_main() {
  uart_init();  // Initialize UART

  // Create a FreeRTOS task to print Hello World
  xTaskCreate(hello_world_task, "hello_world_task", 2048, NULL, 1, NULL);
}
