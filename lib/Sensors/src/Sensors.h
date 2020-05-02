#pragma once

#include <Arduino.h>
#include <ItsTime.h>

// Ova klasa sadrzi sve podatke nedavno prikupljene sa senzora vozila.
class Sensors
{
private:
    static int pinIntR;
    static int pinIntL;
    static int cntR, cntRprev;
    static int cntL, cntLprev;
    //B static ulong secs;
    static ItsTime timStatus;

    static ICACHE_RAM_ATTR void handleIntR() { cntR++; }
    static ICACHE_RAM_ATTR void handleIntL() { cntL++; }

public:
    // Tekuce vreme u milisekundama.
    static ulong ms;

    static void Setup();
    static void Refresh();

};
