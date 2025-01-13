#pragma once

void setupButton(void (*clickHandler)());
void loopButton();
void buttonTask(void* pvParameters);