#pragma once

#include "Status.h"
#include <CircularBuffer.h>

//* ako ovo predje 255 - izmeniti tip brojackih promenljivih u kodu: uint8_t -> ...
#define ST_CAPACITY 2

class Statuses
{
private:
    static CircularBuffer<Status*, ST_CAPACITY> statuses;

    static int GetIdxStart(ulong idLimit);

public:
    static void Add(Status *s);
    // static Status** GetNewStatuses(ulong idLimit = 0);
    // static String* GetNewStatusesLines(ulong idLimit = 0);
    static String GetNewStatusesText(ulong idLimit = 0);
    
};


