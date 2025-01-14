#include <Arduino.h>
#include "config.h"
#include "controllers/ButtonController.h"
#include "controllers/BuzzerController.h"
#include "controllers/LcdController.h"
#include "controllers/LedController.h"
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

  if (strcmp(topic, TOPIC_HAS_BULLET) == 0) {
    gameState.has_bullet = strcmp((char*)data, "True") == 0;
  } else if (strcmp(topic, TOPIC_HAS_WON) == 0) {
    gameState.has_won = strcmp((char*)data, "True") == 0;
    setRows("You won!");
    playMelody(gameWinMelody);
  } else if (strcmp(topic, TOPIC_CAN_MOVE) == 0) {
    gameState.can_move = strcmp((char*)data, "True") == 0;
  } else if (strcmp(topic, TOPIC_HAS_DIED) == 0) {
    gameState.has_died = strcmp((char*)data, "True") == 0;
    if (gameState.has_died) {
      setRows("Game over!");
      playMelody(gameLoseMelody);
    }
  } else if (strcmp(topic, TOPIC_READY) == 0) {
    gameState.ready = strcmp((char*)data, "True") == 0;
  } else if (strcmp(topic, TOPIC_STAGE) == 0) {
    if (strcmp((char*)data, "joining") == 0) {
      gameState.stage = GameState::Stage::Joining;
      setRows("Meeple Showdown!", "Press to join...");
    }
  } else if (strcmp((char*)data, "moving") == 0) {
    gameState.stage = GameState::Stage::Moving;
    setRows("Players are", "moving...");
    stopBlinkTask();
  } else if (strcmp((char*)data, "shooting") == 0) {
    gameState.stage = GameState::Stage::Shooting;
    if (gameState.has_bullet) {
      setRows("Press to shoot!");
      startBlinkTask();
    } else {
      setRows("Waiting for", "shooting...");
    }
  } else if (strcmp((char*)data, "end") == 0) {
    gameState.stage = GameState::Stage::End;
    stopBlinkTask();
  }
}

void handleButtonPress() {
  Serial.println("Button pressed");

  if (gameState.stage == GameState::Stage::Joining) {
    gameState.ready = true;
    setRows("Waiting for", "other players...");
    mqttPublish(TOPIC_READY, "True");
  } else if (gameState.stage == GameState::Stage::Shooting) {
    mqttPublish(TOPIC_SHOOT, "True");
  }
}

void gameLoop() {
  Event event;

  if (xQueueReceive(eventQueue, &event, portMAX_DELAY) == pdTRUE) {
    switch (event.type) {
      case EVENT_MQTT_MESSAGE: {
        MqttMessage* mqttMessage = (MqttMessage*)event.data;

        if (mqttMessage) {
          handleMqttMessage(mqttMessage->topic, mqttMessage->message);

          // Free dynamically allocated memory
          // free(mqttMessage->topic);
          // free(mqttMessage->message);
          // free(mqttMessage);
        }
        break;
      }
      case EVENT_BUTTON_PRESS:
        handleButtonPress();
        break;
    }
  }
}

void gameLoopTask(void* pvParameters) {
  while (true) {
    gameLoop();
  }
}