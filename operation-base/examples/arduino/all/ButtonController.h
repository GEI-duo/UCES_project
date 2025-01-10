#pragma once
#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <PubSubClient.h>

void setupButton();
void checkButtonPress(PubSubClient& client);

#endif
