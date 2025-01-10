#pragma once

#include <ESP8266WiFi.h>

void connect_wifi(const char *ssid, const char *password, int retry_delay);
