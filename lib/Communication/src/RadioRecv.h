#pragma once

#include <Arduino.h>
#include <RH_ASK.h>
#include <SPI.h>
#include "Enums.h"
#include "MotCmd.h"

#define RADIO_DATA_LEN 2

// Objekat ove klase upravlja komunikacijom izmedju volana i vozila.
class RadioRecv
{
private:
    RH_ASK *rh;
    uint8_t n = RADIO_DATA_LEN;
    uint8_t s[RADIO_DATA_LEN];
    bool radioOn = false;
    float xLast, yLast; // poslednje x i y vrednosti izracunate u getMotCmd metodi

public:
    RadioRecv();
    ~RadioRecv();

    bool init();
    RadioRecvCode refresh();
    void end();
    void resume();
    bool isON() { return radioOn; }
    MotCmd *getMotCmd();
};
