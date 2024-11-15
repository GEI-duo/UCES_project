#include "Callbacks.h"

void Callbacks::has_bullet(byte *payload, unsigned int length)
{
    this->player().set_has_bullet(payload[0]);
}

void Callbacks::has_won(byte *payload, unsigned int length)
{
    this->player().set_has_won(payload[0]);
}

void Callbacks::can_move(byte *payload, unsigned int length)
{
    this->player().set_can_move(payload[0]);
}

void Callbacks::has_died(byte *payload, unsigned int length)
{
    this->player().set_has_died(payload[0]);
}

void Callbacks::callback(char *topic, uint8_t *payload, unsigned int length)
{
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    for (unsigned int i = 0; i < length; i++)
    {
        Serial.print((char)payload[i]);
    }
    Serial.println();

    if (strcmp(topic, "state/stage") == 0)
    {
        GameState state = (GameState)payload[0];
        switch (state)
        {
        case JOINING:
            Serial.println("Joining");
            this->m_player.state = JOINING;
            break;
        case WALKING:
            Serial.println("Walking");
            this->m_player.state = WALKING;
            break;
        case SHOOTING:
            Serial.println("Shooting");
            this->m_player.state = SHOOTING;
            break;
        case ENDING:
            Serial.println("Ending");
            this->m_player.state = ENDING;
            break;
        }
        return;
    }
    else
    {
        // Receive player state
        std::string topic_str(topic);

        for (int i = 0; i < 3; i++)
        {
            // Skip two delimiters
            topic_str.erase(0, topic_str.find('/') + 1);
        }

        if (topic_str == "has_bullet")
        {
            has_bullet(payload, length);
        }
        else if (topic_str == "has_won")
        {
            has_won(payload, length);
        }
        else if (topic_str == "can_move")
        {
            can_move(payload, length);
        }
        else if (topic_str == "has_died")
        {
            has_died(payload, length);
        }
    }
}
