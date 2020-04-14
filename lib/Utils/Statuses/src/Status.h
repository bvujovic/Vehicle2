#pragma once

#include <ArduinoV2.h>

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
    
};
