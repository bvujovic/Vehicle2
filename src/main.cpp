#include <Arduino.h>
#include <UtilsESP.h>
#include <UtilsCommon.h>
#include <Statuses.h>

#include "MotorController.h"
MotorController motors;

#include <WiFiServerBasics.h>
ESP8266WebServer server(80);

#include <ArduinoOTA.h>
bool isOtaOn = false; // da li je OTA update u toku

// Akcija vozila (act)
void ActHandler()
{
    // /act?x=0&y=0.1&t=1500&f=0
    String x = server.arg("x");
    String y = server.arg("y");
    String t = server.arg("t");
    String f = server.arg("f");
    MotCmd *cmd = new MotCmd(x.toFloat(), y.toFloat(), t.toInt(), (MotCmdFlags)f.toInt());
    motors.AddCmd(cmd);
    //B Statuses::Add(x + "\t" + y);
    Statuses::Add(new Status(x + ", " + y + ", " + t, "user"));

    server.send(200, "text/plain", "OK");
}

// Statusi sistema (statuses)
void StatusesHandler()
{
    // /statuses?idLimit=123
    String idLimit = server.arg("idLimit");
    //B
    // Statuses::Add(new Status("start", "main"));
    // Statuses::Add(new Status("second"));
    server.send(200, "text/x-csv", Statuses::GetNewStatusesText(idLimit.toInt()));
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
    server.on("/act", ActHandler);
    //* server.on("/tests", VTestsHandler);
    server.on("/statuses", StatusesHandler);
    server.on("/reps/", []() { HandleDataFile(server, "/reps/index.html", "text/html"); });
    server.on("/reps/statuses.html", []() { HandleDataFile(server, "/reps/statuses.html", "text/html"); });
    server.on("/inc/statuses.js", []() { HandleDataFile(server, "/inc/statuses.js", "text/javascript"); });
    server.on("/otaUpdate", []() { server.send(200, "text/plain", ""); isOtaOn = true; ArduinoOTA.begin(); });
    server.begin();
    Serial.println("WiFi ON");
    UtilsESP::PrintBoardStatus();
}

//* Rad sa signalom sa motor speed encoder-a
// const int pinInt1 = D7;
// int cnt1 = 0;
// ICACHE_RAM_ATTR void handleInt1()
// {
//     tprintln("1: ", cnt1++);
// }
// kôd za setup()
//     pinMode(pinInt1, INPUT_PULLUP);
//     attachInterrupt(digitalPinToInterrupt(pinInt1), handleInt1, FALLING);

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, true);
    Serial.begin(115200);
    Serial.println();
    SPIFFS.begin();

    WiFiOn();
}

void loop()
{
    delay(10);

    if (isOtaOn)
    {
        ArduinoOTA.handle();
        return;
    }

    server.handleClient();
    motors.Refresh(millis());
}
