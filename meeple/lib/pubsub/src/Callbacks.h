#pragma once

#include <PubSubClient.h>
#include <string>
#include <Arduino.h>
#include "GamePlayer.h"

class Callbacks
{
public:
    Callbacks(Player &player) : m_player(player) {}

    void callback(char *topic, uint8_t *payload, unsigned int length);
    Player &player() { return m_player; }

private:
    Player &m_player;

    void has_bullet(byte *payload, unsigned int length);
    void has_won(byte *payload, unsigned int length);
    void can_move(byte *payload, unsigned int length);
    void has_died(byte *payload, unsigned int length);
};
