#pragma once

void gameLoop();
void handleMqttMessage(char* topic, void* data);
void handleButtonPress();
void gameLoopTask(void* pvParameters);