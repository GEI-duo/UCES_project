#pragma once
#ifndef LEDCONTROLLER_H
#define LEDCONTROLLER_H

#include <Arduino.h>

void setupLED();
void handleLEDMessage(const String& message);

#endif
