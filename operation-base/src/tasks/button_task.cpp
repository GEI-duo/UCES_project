#include "tasks/button_task.h"
#include "controllers/ButtonController.h"
#include "events.h"

void buttonTask(void* pvParameters) {
  while (true) {
    loopButton();
  }
}