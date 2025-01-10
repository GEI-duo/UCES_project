#include "globals.h"
#include "events.h"

QueueHandle_t eventQueue = NULL;

void eventQueue_init(void) {
  eventQueue = xQueueCreate(10, sizeof(Event));
  if (eventQueue == NULL) {
    Serial.println("Failed to create eventQueue\n");
  } else {
    Serial.println("eventQueue created successfully\n");
  }
}
