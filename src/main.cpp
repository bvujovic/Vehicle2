#include <Arduino.h>
#include <UtilsESP.h>
#include <UtilsCommon.h>
#include <Statuses.h>
#include <VTests.h>
#include <Sensors.h>
#include <ItsTime.h>
#include <SpiffsUtils.h>

#include <EasyINI.h>
EasyINI ei("/config.ini");

#include "MotorController.h"
MotorController motors;

#include <WiFiServerBasics.h>
ESP8266WebServer server(80);

#include <ArduinoOTA.h>
bool isOtaOn = false; // da li je OTA update u toku

#include "RadioRecv.h"
RadioRecv radio;

const int pinLed = LED_BUILTIN;
void ledON(bool on) { digitalWrite(pinLed, !on); }

// Akcija vozila: /act?x=0&y=0.1&t=1500&f=0
void ActHandler()
{
    String x = server.arg("x");
    String y = server.arg("y");
    String t = server.arg("t");
    String f = server.arg("f");
    Sensors::TimStatusStart(250);
    MotCmd *cmd = new MotCmd(x.toFloat(), y.toFloat(), t.toInt(), (MotCmdFlags)f.toInt());
    motors.AddCmd(cmd);
    Statuses::Add(new Status(x + ", " + y + ", " + t, "user"));

    server.send(200, "text/plain", "OK");
}

// VTests - testiranje motora (min/max brzine, balans...): /vtests?k=1&y=300
void VTestsHandler()
{
    String k = server.arg("k"); // vrsta testa (VTestsEnum)
    String y = server.arg("y"); // brzina motora
    VTests::StartTest((VTestsEnum)k.toInt(), (uint)y.toInt());
    server.send(200, "text/plain", "OK");
}

// Statusi sistema: /statuses?idLimit=123
void StatusesHandler()
{
    String idLimit = server.arg("idLimit");
    server.send(200, "text/x-csv", Statuses::GetNewStatusesText(idLimit.toInt()));
}

void ReadConfigIni()
{
    ei.open(FMOD_READ);
    MotCtrlCore::SetLeftCoef(ei.getFloat("MotCtrlCoreLeftCoef"));
    ei.close();
}

String textFileName;

void LoadTextFileHandler()
{
    textFileName = server.arg("name");
    File f = SPIFFS.open(textFileName, "r");
    if (f)
    {
        server.streamFile(f, "text/css");
        f.close();
    }
    else
        Serial.println(textFileName + " - error reading file.");
}

void SaveTextFileHandler()
{
    SpiffsUtils::WriteFile(textFileName, server.arg("plain"));
    server.send(200, "text/plain", "");

    if (textFileName == ei.getFileName())
        ReadConfigIni();
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
    server.on("/text_editor.html", []() { HandleDataFile(server, "/text_editor.html", "text/html"); });
    server.on("/act", ActHandler);
    server.on("/loadTextFile", LoadTextFileHandler);
    server.on("/saveTextFile", SaveTextFileHandler);
    server.on("/vtests", VTestsHandler);
    server.on("/statuses", StatusesHandler);
    server.on("/act.html", []() { HandleDataFile(server, "/act.html", "text/html"); });
    server.on("/reps/", []() { HandleDataFile(server, "/reps/index.html", "text/html"); });
    server.on("/reps/statuses.html", []() { HandleDataFile(server, "/reps/statuses.html", "text/html"); });
    server.on("/inc/statuses.js", []() { HandleDataFile(server, "/inc/statuses.js", "text/javascript"); });
    server.on("/otaUpdate", []() { server.send(200, "text/plain", ""); isOtaOn = true; ArduinoOTA.begin(); });
    server.on("/radioON", []() { server.send(200, "text/plain", ""); radio.resume(); });
    server.begin();
    Serial.println("WiFi ON");
}

// Diskonektovanje sa WiFi-a i odlazak na spavanje. Klik Reset dugme za budjenje.
void Sleep()
{
    server.stop();
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    delay(100);
    ESP.deepSleep(0);
}

void setup()
{
    pinMode(pinLed, OUTPUT);
    ledON(true);
    Serial.begin(115200);
    Serial.println();
    SPIFFS.begin();

    ReadConfigIni();
    Sensors::Setup();
    VTests::SetMotors(&motors);

    WiFiOn();
    radio.init();
    radio.end();
    ledON(false);
}

//B ItsTime timMemory(30000);

void loop()
{
    delay(10);

    if (isOtaOn)
    {
        ArduinoOTA.handle();
        return;
    }
    if (radio.isON())
    {
        RadioRecvCode code = radio.refresh();
        if (code == WheelPos)
        {
            MotCmd *cmd = radio.getMotCmd();
            if (cmd != NULL)
            {
                motors.AddCmd(cmd);
                Statuses::Add(new Status(String(cmd->GetX()) + ", " + cmd->GetY(), "radio"));
            }
        }
    }
    else
        server.handleClient();
    //B
    // if (timMemory.IsTick())
    //     Statuses::Add(String(UtilsESP::GetFreeMemKB()), "free mem");

    Sensors::ms = millis();
    Sensors::Refresh();
    VTests::Refresh();
    motors.Refresh();
}
