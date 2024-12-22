#pragma once
#ifndef BUZZERCONTROLLER_H
#define BUZZERCONTROLLER_H

#include <Arduino.h>

void setupBuzzer();
void handleBuzzerMessage(const String& message);

#endif
