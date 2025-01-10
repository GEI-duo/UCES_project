#include "MqttManager.h"
#include "config.h"
#include "controllers/BuzzerController.h"
#include "controllers/LcdController.h"
#include "controllers/LedController.h"
#include "events.h"

extern QueueHandle_t eventQueue;

WiFiClient espClient;
PubSubClient client(espClient);

void mqtt_init() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
  client.setCallback(mqtt_callback);
}

void mqtt_reconnect() {
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    if (client.connect("ESP32Client", MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Connected to MQTT Broker!");
      client.subscribe(TOPIC_SHOOT);
      client.subscribe(TOPIC_READY);
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

void mqtt_callback(char* topic, byte* payload, unsigned int length) {
  // Print the topic
  Serial.print("Message arrived on topic: ");
  if (topic != nullptr) {
    Serial.println(topic);
  } else {
    Serial.println("(null)");
  }

  // Print the payload
  Serial.print("Message: ");
  if (payload != nullptr && length > 0) {
    for (unsigned int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
  } else {
    Serial.println("(empty)");
  }

  // Create a String for the message payload
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  // Send the event to the queue
  Event event;
  event.type = EVENT_MQTT_MESSAGE;

  // Allocate memory to store the topic string dynamically (to avoid overwriting)
  char* topicCopy = strdup(topic);
  if (topicCopy == nullptr) {
    Serial.println("Error: Memory allocation failed for topic.");
    return;
  }

  event.data = (void*)topicCopy;  // Store the topic copy in the event

  if (xQueueSend(eventQueue, &event, portMAX_DELAY) != pdPASS) {
    Serial.println("Error: Failed to send event to the queue.");
    free(topicCopy);  // Free the allocated memory if the queue send fails
  }
}

void mqtt_publish(const char* topic, const char* message) {
  client.publish(topic, message);
}