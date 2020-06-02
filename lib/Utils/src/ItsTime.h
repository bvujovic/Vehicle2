#pragma once

#include <Arduino.h>

// Za zadati interval u milisekundama, metoda IsTick() vraca true kada ovaj istekne.
class ItsTime
{
private:
    uint msInterval; // Vremenski interval tajmera - na koliko ce milisekundi IsTick() vratiti true.
    ulong msStarted; // Trenutak (u ms) kada je pokrenut ovaj timer.
    uint cnt;        // Brojac uz pomoc kojeg se utvrdjuje da li IsTick() vraca true ili false.
    bool enabled;    // Da li je tajmer pokrenut ili ne.

public:
    // Konstruktor u koji treba proslediti interval (u milisekundama) na koji ce se izvrsavati neka akcija.
    ItsTime(uint msInterval, bool enabled = true);
    // Podesavanje intervala (u ms) na koji ce metod Tick() vratiti true.
    void SetInterval(uint msInterval) { this->msInterval = msInterval; }
    // Pocetak/Nastavak rada (true) ili Pauza (false).
    void SetEnabled(bool enabled);
    // Provera da li je vreme za neki redovni dogadjaj. U loop()-u : if (tim.IsTick()) DoSomething();
    bool IsTick();
};
