#pragma once

#include <Arduino.h>

// Za zadati interval u milisekundama, metoda IsTick() vraca true kada ovaj istekne.
class ItsTime
{
private:
    uint msInterval;
    uint cnt = 0;
    bool enabled;

public:
    // Konstruktor u koji treba proslediti interval (u milisekundama) na koji ce se izvrsavati neka akcija.
    ItsTime(uint msInterval, bool enabled = true)
    {
        SetInterval(msInterval);
        SetEnabled(enabled);
    }
    // Podesavanje intervala (u ms) na koji ce metod Tick() vratiti true.
    void SetInterval(uint msInterval) { this->msInterval = msInterval; }
    // Pocetak/Nastavak rada (true) ili Pauza (false).
    void SetEnabled(bool enabled) { this->enabled = enabled; }
    // Provera da li je vreme za neki redovni dogadjaj. U loop()-u : if (tim.IsTick()) DoSomething();
    bool IsTick();
};
