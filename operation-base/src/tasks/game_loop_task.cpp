#include "tasks/button_task.h"
#include "managers/GameManager.h"
#include "events.h"

void gameLoopTask(void* pvParameters) {
  while (true) {
    gameLoop();
  }
}