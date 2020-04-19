#include "Statuses.h"

CircularBuffer<Status *, ST_CAPACITY> Statuses::statuses;

void Statuses::Add(Status *s)
{
    statuses.unshift(s);
}

//B
// Status **Statuses::GetNewStatuses(ulong idLimit)
// {
//     int cnt = 0; // prebrojavanje koliko ima novih statusa (id > idLimit)
//     for (int i = 0; i < statuses.size(); i++) // petlja ide od kraja ka pocetku spiska statusa
//         if (statuses[i]->GetId() > idLimit)
//             cnt++;
//         else
//             break;
//     if (cnt == 0)
//         return NULL;
//     else
//     {
//         Status **res = new Status *[12];
//         for (int i = cnt - 1; i >= 0; i--)
//             res[i] = statuses[i];
//         return res;
//     }
// }

int Statuses::GetIdxStart(ulong idLimit)
{
    int i = 0;
    for (; i < statuses.size(); i++) // petlja ide od kraja ka pocetku spiska statusa
        if (statuses[i]->GetId() <= idLimit)
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