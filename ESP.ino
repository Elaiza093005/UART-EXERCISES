#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "AKINLANGSIAIAH";
const char* password = "SIGETAWANANMOAKO";

WebServer server(80);

void setup() {
  Serial.begin(115200);                    
  delay(1000);                             

  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("Serial2 started...");

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Root route (HTML with buttons)
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html",
      "<h1>Control LED</h1>"
      "<a href='/on'><button style='font-size:24px;'>ON</button></a> "
      "<a href='/off'><button style='font-size:24px;'>OFF</button></a>");
  });

  // Handle /on
  server.on("/on", []() {
    Serial2.println("ON");
    Serial.println("Sent: ON");
    server.send(200, "text/plain", "LED ON");
  });

  // Handle /off
  server.on("/off", []() {
    Serial2.println("OFF");
    Serial.println("Sent: OFF");
    server.send(200, "text/plain", "LED OFF");
  });

  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();

  // (Optional) Read response from Arduino
  if (Serial2.available()) {
    String msg = Serial2.readStringUntil('\n');
    Serial.print("Arduino: ");
    Serial.println(msg);
  }
}
