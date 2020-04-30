#pragma once

#include <ArduinoV2.h>

// Status sistema: poruka/tekst, izvor/uzrok poruke, vreme kreiranja statusa i id.
class Status
{
private:
    ulong id;
    ulong ms;
    String message;
    String source;

    static ulong idGenerator;

public:
    Status(String message, String source, ulong ms);
    Status(String message, String source = "");

    String ToString();
    
    // Status id
    ulong GetId() { return id; }
    // Vreme (u milisekundama) kada je status kreiran
    ulong GetMs() { return ms; }
    // Statusna poruka
    String GetMessage() { return message; }
    // Izvor/poreklo statusa
    String GetSource() { return source; }
};
