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
    float xLast, yLast;     // Poslednje x i y vrednosti izracunate u getMotCmd metodi.
    static int8_t minPitch; // Najmanji pitch ugao volana na koji vozilo reaguje. Ispod toga vozilo stoji.
    static int8_t maxAngle; // Najveci pitch/roll ugao koji se racuna. Veci ugao volana ne pravi vecu brzinu/skretanje.
    static float pitchInvCoef; // Veci broj -> blaze reakcije vozila. Manji broj -> ostrije reakcije i veca max brzina.

public:
    RadioRecv();
    ~RadioRecv();

    bool init();
    RadioRecvCode refresh();
    void end();
    void resume();
    bool isON() { return radioOn; }
    MotCmd *getMotCmd();
    static void SetStWheelMinPitch(int8_t pitch) { minPitch = constrain(pitch, 2, 20); }
    static void SetStWheelMaxAngle(int8_t angle) { maxAngle = constrain(angle, 25, 120); }
    static void SetStWheelPitchInvCoef(float coef) { pitchInvCoef = constrain(coef, 100, 1000); }
};
