#include "MqttSetup.h"

void _subscribe(PubSubClient &client, const char *username)
{
    const std::string topics[] = {
        "state/stage",
        "players/" + std::string(username) + "/state/+"};

    for (const auto &topic : topics)
    {
        Serial.printf("Subscribing to %s ... ", topic.c_str());
        if (client.subscribe(topic.c_str()))
        {
            Serial.println("OK");
        }
        else
        {
            Serial.println("ERROR");
        }
    }
}

void init_mqtt_client(PubSubClient &mqtt_client, const char *mqtt_server_host, int mqtt_server_port, Callbacks &callbacks)
{
    mqtt_client.setServer(mqtt_server_host, mqtt_server_port);
    mqtt_client.setCallback([&callbacks](char *topic, uint8_t *payload, unsigned int length)
                            { callbacks.callback(topic, payload, length); });
}

void reconnect(PubSubClient &client, const char *username, const char *password, int reconnect_delay, Callbacks &callbacks)
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect, just a name to identify the client
        if (client.connect(username, username, password))
        {
            Serial.println("OK");
        }
        else
        {
            Serial.print("ERROR, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(reconnect_delay);
        }
    }
    _subscribe(client, callbacks.player().username());
}