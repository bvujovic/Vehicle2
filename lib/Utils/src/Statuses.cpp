#include "Statuses.h"
#include <UtilsCommon.h>

CircularBuffer<Status *, STAT_CAPACITY> Statuses::statuses;

void Statuses::Add(Status *s)
{
    tprintln(s->ToString());
    statuses.unshift(s);
}

void Statuses::Add(String str)
{
    Add(new Status(str));
}

int Statuses::GetIdxStart(ulong id)
{
    int i = 0;
    for (; i < statuses.size(); i++) // petlja ide od kraja ka pocetku spiska statusa
        if (statuses[i]->GetId() <= id)
            break;
    return i;
}

String Statuses::GetNewStatusesText(ulong idLimit)
{
    int idxStart = GetIdxStart(idLimit);
    if (idxStart == 0)
        return "";
    String res;
    for (int i = 0; i < idxStart - 1; i++)
    {
        res.concat(statuses[i]->ToString());
        res.concat('\n');
    }
    res.concat(statuses[idxStart - 1]->ToString());
    return res;
}