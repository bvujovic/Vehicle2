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
    // Time (in milliseconds) when the status was created
    ulong GetMs() { return ms; }
    // Status message
    String GetMessage() { return message; }
    // Source (origin) of the status
    String GetSource() { return source; }
};
