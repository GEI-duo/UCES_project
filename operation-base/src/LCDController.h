#pragma once
#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

#include <Arduino.h>

void setupLCD();
void handleLCDMessage(const String& message);

#endif
