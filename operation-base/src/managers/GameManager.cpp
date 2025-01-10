#include <Arduino.h>
#include "config.h"
#include "controllers/LcdController.h"
#include "events.h"
#include "globals.h"
#include "managers/MqttManager.h"

struct GameState {
  bool has_bullet;
  bool has_won;
  bool can_move;
  bool has_died;
  bool ready;

  enum class Stage { Joining, Moving, Shooting, End } stage;

  std::string getStageAsString() const {
    switch (stage) {
      case Stage::Joining:
        return "joining";
      case Stage::Moving:
        return "moving";
      case Stage::Shooting:
        return "shooting";
      case Stage::End:
        return "end";
      default:
        return "unknown";
    }
  }
};

GameState gameState = {.has_bullet = false,
                       .has_won = false,
                       .can_move = false,
                       .has_died = false,
                       .ready = false,
                       .stage = GameState::Stage::Joining};

void handleMqttMessage(char* topic, void* data) {
  if (topic == nullptr || data == nullptr) {
    Serial.println("Error: MQTT message received with null topic or data.");
    return;
  }

  const char* message = static_cast<const char*>(data);

  Serial.printf(
      "Game Manager: MQTT message received\n  topic: %s\n  message: %s\n",
      topic, message);

  if (strcmp(topic, TOPIC_HAS_BULLET) == 0) {
    gameState.has_bullet = strcmp((char*)data, "True") == 0;
  } else if (strcmp(topic, TOPIC_HAS_WON) == 0) {
    gameState.has_won = strcmp((char*)data, "True") == 0;
  } else if (strcmp(topic, TOPIC_CAN_MOVE) == 0) {
    gameState.can_move = strcmp((char*)data, "True") == 0;
  } else if (strcmp(topic, TOPIC_HAS_DIED) == 0) {
    gameState.has_died = strcmp((char*)data, "True") == 0;
  } else if (strcmp(topic, TOPIC_READY) == 0) {
    gameState.ready = strcmp((char*)data, "True") == 0;
  } else if (strcmp(topic, TOPIC_STAGE) == 0) {
    if (strcmp((char*)data, "joining") == 0) {
      gameState.stage = GameState::Stage::Joining;
    } else if (strcmp((char*)data, "moving") == 0) {
      gameState.stage = GameState::Stage::Moving;
    } else if (strcmp((char*)data, "shooting") == 0) {
      gameState.stage = GameState::Stage::Shooting;
    } else if (strcmp((char*)data, "end") == 0) {
      gameState.stage = GameState::Stage::End;
    }
  }
}

void handleButtonPress() {
  if (gameState.stage == GameState::Stage::Joining) {
    mqtt_publish(TOPIC_READY, "True");
  } else if (gameState.stage == GameState::Stage::Shooting) {
    mqtt_publish(TOPIC_SHOOT, "True");
  }
}

void gameLoop() {
  Event event;

  // LCD messages
  // "Press to join"
  // "Waiting for other players"
  // "Players are moving"
  // "Press to shoot"
  // "Wait for shooting"
  // "Victory"
  // "Game over"

  if (gameState.stage == GameState::Stage::Joining) {
    if (gameState.ready) {}
  } else if (gameState.stage == GameState::Stage::Moving) {
    if (gameState.can_move) {
      // Move player
    }
  } else if (gameState.stage == GameState::Stage::Shooting) {
    if (gameState.has_bullet) {
      // Shoot
    }
  } else if (gameState.stage == GameState::Stage::End) {
    if (gameState.has_won) {
      // Victory
    } else {
      // Game over
    }
  }

  if (xQueueReceive(eventQueue, &event, portMAX_DELAY) == pdTRUE) {
    switch (event.type) {
      case EVENT_MQTT_MESSAGE:
        handleMqttMessage(((MqttMessage*)event.data)->topic,
                          ((MqttMessage*)event.data)->message);
        break;
      case EVENT_BUTTON_PRESS:
        Serial.println("Button pressed");
        handleButtonPress();
        break;
    }
  }
}
