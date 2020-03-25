#pragma once

#include <TestArduino.h>
#include "Enums.h"

// Komanda/zadatak za MotorController.
class MotCmd
{
private:
    float x;           // Smer kretanja. 0 pravo, <0 ulevo, >0 udesno
    float y;           // Brzina kretanja. 0 stop, <0 unazad, >0 unapred
    int t;             // Trajanje komande u ms
    MotCmdFlags flags; // Razliciti parametri komande, npr: brake, cancelled

    static const float MIN; // minimalna vrednost za x i y
    static const float MAX; // maksimalna vrednost za x i y

public:
    MotCmd();
    MotCmd(float x, float y, int t, MotCmdFlags flags);

    float GetX() { return x; }
    float GetY() { return y; }
    int GetT() { return t; }
    MotCmdFlags GetFlags() { return flags; }

    void SetX(float x) { this->x = constrain(x, MIN, MAX); }
    void SetY(float y) { this->y = constrain(y, MIN, MAX); }
    void SetT(int t) { this->t = t >= 0 ? t : 0; }
    void SetFlags(MotCmdFlags flags) { this->flags = flags; }
};
