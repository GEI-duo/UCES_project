#include "MQTTManager.h"
#include <WiFi.h>
#include "BuzzerController.h"
#include "Config.h"
#include "LCDController.h"
#include "LEDController.h"

void setupMQTT(PubSubClient& client) {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqttCallback);
}

void reconnectMQTT(PubSubClient& client) {
  while (!client.connected()) {
    if (client.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)) {

      Serial.println("Connected to MQTT broker!");

      client.subscribe(TOPIC_LED);
      client.subscribe(TOPIC_BUZZER);
      client.subscribe(TOPIC_LCD);
    } else {
      delay(5000);
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (strcmp(topic, TOPIC_LED) == 0) {
    handleLEDMessage(message);
  } else if (strcmp(topic, TOPIC_BUZZER) == 0) {
    handleBuzzerMessage(message);
  } else if (strcmp(topic, TOPIC_LCD) == 0) {
    handleLCDMessage(message);
  }
}
