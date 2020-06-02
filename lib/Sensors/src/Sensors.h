#pragma once

#include <Arduino.h>
#include <ItsTime.h>

// Ova klasa sadrzi sve podatke nedavno prikupljene sa senzora vozila.
class Sensors
{
private:
    static uint pinIntR;
    static uint pinIntL;
    static uint cntR, cntRprev;
    static uint cntL, cntLprev;
    //B static ulong secs;
    static ItsTime timStatus;

    static ICACHE_RAM_ATTR void handleIntR() { cntR++; }
    static ICACHE_RAM_ATTR void handleIntL() { cntL++; }

public:
    // Tekuce vreme u milisekundama.
    static ulong ms;

    static uint GetEncoderCntR() { return cntR; }
    static uint GetEncoderCntL() { return cntL; }

    static void Setup();
    static void Refresh();
    static void TimStatusStart(uint msInterval = 0);
};
