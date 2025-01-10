# Operation Base

## Game

### Objective
Be the last surviving meeple on the board.

### Players
Each team consists of two people:
- Mover (Pawn Controller): Controls the movement of the meeple on the board.
- Operator (Strategist): Makes decisions on whether to shoot or pass the bullet without seeing the board.

### Game components
- Magnetic board(s) with hidden magnets under each position.
- Meeples (pawns): each player team has one meeple. It has two leds, one for knowing who has the bullet and another for the magnet detection feedback.
- Operation Base: includes LCD display, push button, and other components for decisions made by operators.
- Broker: it handles the game logic and the state.

### Setup
- Initial Meeple Placement: Each pawn begins in a random position on the board. This is decided before the game starts.
- Bullet Assignment: One player is randomly assigned the Bullet at the start of the game.

### Game Flow
The game proceeds in rounds, with the following steps repeated until only one meeple remains:
1. Movement Phase:
    - Pawns move one space in one of four directions: up, down, left, or right.
    - Movement order is decided randomly at the start of each round.
2. Decision Phase:
    - The operator of the team with the Bullet decides if they want to shoot.
    - The operator cannot see the board, but may communicate with other pawns (within 60 seconds).
    - Shooting affects all meeples in the same row, column or diagonal as the operator’s meeple.
        - Hit: If the shot hits any meeples, they are eliminated.
        - Miss: If no other meeple is hit, the shooting operator is eliminated.
    - If the operator chooses not to shoot, he has a small probability of dying.

## MQTT Topics
players/{player_id}
                    /actions
                        /die: bool
                        /shoot: bool
                        /move: bool
                        /ready
                            /meeple: bool
                            /base: bool
                    /state
                        /has_bullet: bool
                        /has_won: bool
                        /can_move: bool
                        /had_died: bool
state/stage: "joining" | "moving" | "shooting" | "end" 

### End condition
The game continues until only one meeple remains. This team is declared the winner.


## Project structure
/src
    main.cpp
    /tasks
        wifi_task.cpp
        wifi_task.h
            void wifiTask(void* pvParameters);
        mqtt_task.cpp
        mqtt_task.h
            void mqttTask(void* pvParameters);
        button_task.cpp
        button_task.h
            void buttonTask(void* pvParameters);
    /managers
        WifiManager.cpp
        WifiManager.h
            void setupWifi();
            void loopWifi();
        MqttManager.cpp
        MqttManager.h
            class MqttManager;
            void setupMqtt(PubSubClient& client);
            void reconnectMqtt(PubSubClient& client);
            void mqttCallback(char* topic, byte* payload, unsigned int length);

    /controllers
        ButtonController.cpp
        ButtonController.h
            void setupButton(void (*onClick)());
            void loopButton();
        LcdController.cpp
        LcdController.h
            void setupLcd();
        BuzzerController.cpp
        BuzzerController.h
            void setupBuzzer();
        LedController.cpp
        LedController.h
            void setupLed();
    config.h
    config.cpp
    globals.h
    globals.cpp


## Program flow
1. The `broker` sets the "joining" stage.                       
2. The `base` and the `meeple` can send their "ready" state.
3. When all players are ready, the `broker` changes the state to "moving".
4. While not all players have moved:
    4.1. The `broker` set the "can_move" state to true to the next player.
    4.2. The `meeple` sets the "move" state to true after moving.
5. After all players have moved, the `broker` changes the state to "shooting".
6. The `broker` sets the "has_bullet" state to true to a random player.
7. The `base` sets the "shoot" state to decide the shooting.
8. The `meeple`s send the "die" action if they were hit.
9. If no player was hit (10s after shooting), the `broker` sets the "had_died" state to true to the shooting player.
10. If there is only one player remaining, the `broker` changes the state to "end" and sets the "has_won" state to true to the winner.
11. Repeat steps 3 to 10 until the game ends. 