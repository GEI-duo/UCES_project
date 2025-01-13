#include "MqttManager.h"
#include "config.h"
#include "controllers/BuzzerController.h"
#include "controllers/LcdController.h"
#include "controllers/LedController.h"
#include "events.h"
#include "globals.h"

extern QueueHandle_t eventQueue;

WiFiClient espClient;
PubSubClient client(espClient);

void mqttInit() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqttCallback);
}

void mqttReconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("duo_jc_base", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT Broker!");
      client.subscribe(TOPIC_SHOOT);
      client.subscribe(TOPIC_HAS_BULLET);
      client.subscribe(TOPIC_HAS_WON);
      client.subscribe(TOPIC_CAN_MOVE);
      client.subscribe(TOPIC_HAS_DIED);
      client.subscribe(TOPIC_STAGE);
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" Trying again in 5 seconds...");
      vTaskDelay(pdMS_TO_TICKS(5000));
    }
  }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("MQTT message received: ");

  if (topic) {
    Serial.print(topic);
  } else {
    Serial.print("(null)");
  }

  Serial.print(" = ");

  if (payload != nullptr && length > 0) {
    for (unsigned int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
  } else {
    Serial.print("(empty)");
  }

  Serial.println();

  // Create and populate the MqttMessage struct
  MqttMessage* message = (MqttMessage*)malloc(sizeof(MqttMessage));
  if (message == nullptr) {
    Serial.println("Error: Memory allocation failed for MqttMessage.");
    return;
  }

  // Allocate memory for the topic
  message->topic = strdup(topic);
  if (message->topic == nullptr) {
    Serial.println("Error: Memory allocation failed for topic.");
    free(message);  // Free the message structure
    return;
  }

  // Allocate memory for the message payload
  message->message = (char*)malloc(length + 1);  // +1 for null-termination
  if (message->message == nullptr) {
    Serial.println("Error: Memory allocation failed for message.");
    free(message->topic);
    free(message);
    return;
  }

  // Copy the payload into the allocated memory
  memcpy(message->message, payload, length);
  message->message[length] = '\0';  // Null-terminate the message string

  // Create the event
  Event event;
  event.type = EVENT_MQTT_MESSAGE;
  event.data = (void*)message;

  // Send the event to the queue
  if (xQueueSend(eventQueue, &event, portMAX_DELAY) != pdPASS) {
    Serial.println("Error: Failed to send event to the queue.");
    free(message->topic);
    free(message->message);
    free(message);
  }
}

void mqttPublish(const char* topic, const char* message) {
  client.publish(topic, message);
}

void mqttTask(void* pvParameters) {
  while (1) {
    if (!client.connected()) {
      mqttReconnect();
    }
    client.loop();
    vTaskDelay(pdMS_TO_TICKS(1000));
  }
}