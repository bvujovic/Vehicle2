#include "Statuses.h"
#include <UtilsCommon.h>

CircularBuffer<Status *, STAT_CAPACITY> Statuses::statuses;

void Statuses::Add(Status *s)
{
    tprintln(s->ToString());
    statuses.unshift(s);
}

void Statuses::Add(String msg, String src)
{
    Add(new Status(msg, src));
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
    for (int i = idxStart - 1; i > 0; i--)
    {
        res.concat(statuses[i]->ToString());
        res.concat('\n');
    }
    res.concat(statuses[0]->ToString());
    return res;
}