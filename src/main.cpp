#include <Arduino.h>
#include "Utils.h"

#include "MotorController.h"
MotorController motors;

#include <WiFiServerBasics.h>
ESP8266WebServer server(80);

// Akcija vozila (act)
void HandleAction()
{
    // act?x=0.33&y=-0.5&t=1500
    String x = server.arg("x");
    Serial.println(x);
    String y = server.arg("y");
    Serial.println(y);
    String t = server.arg("t");
    Serial.println(t);

    Vector v(x.toFloat(), y.toFloat());
    motors.Go(v, t.toFloat());

    // server.send(200, "application/json", "{}");
    server.send(200, "text/plain", "OK");
}

// Konektovanje na WiFi, uzimanje tacnog vremena, postavljanje IP adrese i startovanje veb servera.
void WiFiOn()
{
    Serial.println("Turning WiFi ON...");
    WiFi.mode(WIFI_STA);
    ConnectToWiFi();
    SetupIPAddress(50);
    server.on("/", []() { HandleDataFile(server, "/index.html", "text/html"); });
    server.on("/inc/vehicle.png", []() { HandleDataFile(server, "/inc/vehicle.png", "image/png"); });
    server.on("/inc/script.js", []() { HandleDataFile(server, "/inc/script.js", "text/javascript"); });
    server.on("/inc/style.css", []() { HandleDataFile(server, "/inc/style.css", "text/css"); });
    server.on("/act", HandleAction);
    server.begin();
    Serial.println("WiFi ON");
}

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, true);
    Serial.begin(115200);
    SPIFFS.begin();
    WiFiOn();
}

void loop()
{
    server.handleClient();
    delay(10);
}