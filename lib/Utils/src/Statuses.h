#pragma once

#include "Status.h"
#include <CircularBuffer.h>

//* ako ovo predje 255 - izmeniti tip brojackih promenljivih u kodu: uint8_t -> ...
#define STAT_CAPACITY 20

// Kolekcija (CircularBuffer) statusa sistema.
class Statuses
{
private:
    static CircularBuffer<Status *, STAT_CAPACITY> statuses;
    // Metoda vraca indeks statusa u kolekciji statuses za status sa prosledjenim id-em.
    static int GetIdxStart(ulong id);

public:
    // Dodavanje novog statusa u kolekciju.
    static void Add(Status *s);
    // Dodavanje novog statusa u kolekciju na osnovu prosledjenie poruke i izvora/uzroka.
    static void Add(String msg, String src = "");
    // Metoda vraca string sastavljen od svih novih (id > idLimit) statusa.
    static String GetNewStatusesText(ulong idLimit = 0);

};
