#include "WifiSetup.h"

bool server_started = false;

const char *wifi_ssid, *wifi_password;

bool connect_wifi(const char *ssid, const char *password)
{
    Serial.printf("Connecting to %s ... ", ssid);
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