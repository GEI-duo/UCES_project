#include "GamePlayer.h"

GameState gamestate_from_name(char *name)
{
    if (strcmp(name, "joining") == 0)
    {
        return JOINING;
    }
    else if (strcmp(name, "moving") == 0)
    {
        return MOVING;
    }
    else if (strcmp(name, "shooting") == 0)
    {
        return SHOOTING;
    }
    else if (strcmp(name, "ending") == 0)
    {
        return ENDING;
    }
    return UNKNOWN;
}