#pragma once

enum EventType {
  EVENT_MQTT_MESSAGE,
  EVENT_BUTTON_PRESS,
};

struct MqttMessage {
  char* topic;
  char* message;
};

struct Event {
  EventType type;
  void* data;  // Pointer to event-specific data
};