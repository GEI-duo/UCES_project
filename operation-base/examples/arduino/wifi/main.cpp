#include <WiFi.h>

const char* ssid = "MIWIFI_2G_aYUz";   // Replace with your WiFi SSID
const char* password = "0123456789j";  // Replace with your WiFi password

void setup() {
  // Start the Serial Monitor
  Serial.begin(115200);
  delay(1000);

  // Connect to WiFi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait for the connection to establish
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  // Once connected, print the IP address
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Keep the loop empty for this example
}
