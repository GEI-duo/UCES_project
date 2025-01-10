#pragma once

#include <PubSubClient.h>
#include <Arduino.h>
#include <string>

typedef enum game_state
{
    JOINING,
    MOVING,
    SHOOTING,
    ENDING,
    UNKNOWN
} GameState;

GameState gamestate_from_name(char *name);

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

    void update_state(char *new_state_name)
    {
        GameState new_state = gamestate_from_name(new_state_name);

        if (new_state == UNKNOWN)
        {
            Serial.printf("[ERROR] UNKNOWN NEW STATE %s\n", new_state_name);
        }

        state = new_state;
    }

    Player(const char *username, PubSubClient &mqtt_client)
        : m_username(username), m_mqtt_client(mqtt_client)
    {
    }

    void reset(void)
    {
        m_can_move = false;
        m_has_bullet = false;
        m_has_won = false;
        m_has_died = false;
    }

    void publish_ready(void) const
    {
        std::string topic = std::string("players/") + m_username + "/actions/ready/meeple";
        publish(topic, "1");
    }

    void publish_moved(void) const
    {
        std::string topic = std::string("players/") + m_username + "/actions/moved";
        publish(topic, "1");
    }

    void publish_died(void) const
    {
        std::string topic = std::string("players/") + m_username + "/actions/die";
        publish(topic, "1");
    }

    bool can_move()
    {
        return m_can_move;
    }

    bool has_bullet()
    {
        return m_has_bullet;
    }

    bool has_won()
    {
        return m_has_won;
    }

    bool has_died()
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