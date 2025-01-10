#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "mqtt_client.h"

static const char *TAG = "MQTT";

static void mqtt_event_handler(void *handler_args, esp_event_base_t base, 
                               int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t) event_data;

    switch (event->event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "Connected to MQTT broker");
        esp_mqtt_client_subscribe(event->client, "/topic/test", 0);
        esp_mqtt_client_publish(event->client, "/topic/test", "Hello, MQTT!", 0, 1, 0);
        break;

    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "Received topic: %.*s, data: %.*s", 
                 event->topic_len, event->topic, event->data_len, event->data);
        break;

    default:
        break;
    }
}

void mqtt_app_start(void) {
    esp_mqtt_client_config_t mqtt_cfg = {};
    mqtt_cfg.broker.address.uri = "mqtt://broker.hivemq.com";  // Public MQTT broker for testing

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, (esp_mqtt_event_id_t)ESP_EVENT_ANY_ID, mqtt_event_handler, client);
    esp_mqtt_client_start(client);
}
