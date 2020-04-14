#pragma once

#include "Status.h"
#include <CircularBuffer.h>

class Statuses
{
private:
    static CircularBuffer<Status*, 20> statuses;

public:
    static void Add(Status *s);
    static Status** GetNewStatuses(ulong idLimit);
    static String* GetNewStatusesLines(ulong idLimit);
    static String GetNewStatusesText(ulong idLimit);
    
};


