#include "WifiSetup.h"

bool wifi_connected = false;
int wifi_connection_attempt = 1;

const char *wifi_ssid, *wifi_password;

bool _connect(const char *ssid, const char *password)
{
    Serial.printf("Connecting to %s with password %s ... ", ssid, password);
    WiFi.begin(ssid, password);

    if (WiFi.waitForConnectResult() == WL_CONNECTED)
    {
        Serial.println("OK");
        Serial.print("IP address:");
        Serial.println(WiFi.localIP());

        wifi_ssid = ssid;
        wifi_password = password;
        return true;
    }

    Serial.println("ERROR");
    WiFi.disconnect(true);
    return false;
}

void connect_wifi(const char *ssid, const char *password, int retry_delay)
{
    while (!wifi_connected)
    {
        wifi_connected = _connect(ssid, password);
        if (!wifi_connected)
        {
            Serial.printf("Attempt %d failed to connect to WiFi, retrying in %ds ...\n", wifi_connection_attempt++, retry_delay / 1000);
            delay(retry_delay);
        }
    }
    wifi_connection_attempt = 1;
}