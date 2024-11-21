#include "Callbacks.h"

void Callbacks::has_bullet(byte *payload, unsigned int length)
{
    this->player().set_has_bullet(payload[0]);
    Serial.printf("Has bullet: %d\n", this->player().has_bullet());
}

void Callbacks::has_won(byte *payload, unsigned int length)
{
    this->player().set_has_won(payload[0]);
    Serial.printf("Has won: %d\n", this->player().has_won());
}

void Callbacks::can_move(byte *payload, unsigned int length)
{
    this->player().set_can_move(payload[0]);
    Serial.printf("Can move: %d\n", this->player().can_move());
}

void Callbacks::has_died(byte *payload, unsigned int length)
{
    this->player().set_has_died(payload[0]);
    Serial.printf("Has died: %d\n", this->player().has_died());
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
        char name[length + 1];
        memcpy(name, payload, length);
        name[length] = '\0';

        GameState state = gamestate_from_name(name);
        switch (state)
        {
        case JOINING:
            Serial.println("[DEBUG] New state! JOINING");
            this->m_player.state = JOINING;
            break;
        case WALKING:
            Serial.println("[DEBUG] New state! WALKING");
            this->m_player.state = WALKING;
            break;
        case SHOOTING:
            Serial.println("[DEBUG] New state! SHOOTING");
            this->m_player.state = SHOOTING;
            break;
        case ENDING:
            Serial.println("[DEBUG] New state! ENDING");
            this->m_player.state = ENDING;
            break;
        default:
            Serial.printf("[ERROR] UNKNOWN NEW STATE %s\n", state);
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
