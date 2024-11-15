#pragma once

#include <PubSubClient.h>
#include <Arduino.h>

typedef enum game_state
{
    JOINING,
    WALKING,
    SHOOTING,
    ENDING
} GameState;

class Player
{
private:
    const char *m_username;
    PubSubClient &m_mqtt_client;
    bool m_can_move;
    bool m_has_bullet;
    bool m_has_won;
    bool m_has_died;

    inline void publish(std::string &topic, const char *message) const
    {
        Serial.printf("Publishing [%s] to %s ... ", message, topic.c_str());
        if (this->m_mqtt_client.publish(topic.c_str(), message))
        {
            Serial.println("OK");
        }
        else
        {
            Serial.println("ERROR");
        }
    }

public:
    GameState state = JOINING;

    Player(const char *username, PubSubClient &mqtt_client)
        : m_username(username), m_mqtt_client(mqtt_client)
    {
    }

    void publish_ready(void) const
    {
        std::string topic = std::string("players/") + m_username + "/actions/ready/meeple";
        publish(topic, "1");
    }

    bool can_move() const
    {
        return m_can_move;
    }

    bool has_bullet() const
    {
        return m_has_bullet;
    }

    bool has_won() const
    {
        return m_has_won;
    }

    bool has_died() const
    {
        return m_has_died;
    }

    void set_can_move(bool can_move)
    {
        m_can_move = can_move;
    }

    void set_has_bullet(bool has_bullet)
    {
        m_has_bullet = has_bullet;
    }

    void set_has_won(bool has_won)
    {
        m_has_won = has_won;
    }

    void set_has_died(bool has_died)
    {
        m_has_died = has_died;
    }

    const char *username() const
    {
        return m_username;
    }
};