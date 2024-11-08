#include "MqttSetup.h"

void _callback(char *topic, byte *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();
}

void _subscribe(PubSubClient &client)
{
    client.subscribe("hello-world/");
}

void init_mqtt_client(PubSubClient &mqtt_client, const char *mqtt_server_host, int mqtt_server_port)
{
    mqtt_client.setServer(mqtt_server_host, mqtt_server_port);
    mqtt_client.setCallback(_callback);
    _subscribe(mqtt_client);
}

void reconnect(PubSubClient &client, const char *username, const char *password, int reconnect_delay)
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Attempt to connect, just a name to identify the client
        if (client.connect("MEEPLE-JC", username, password))
        {
            Serial.println("OK");
            _subscribe(client);
        }
        else
        {
            Serial.print("ERROR, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(reconnect_delay);
        }
    }
}