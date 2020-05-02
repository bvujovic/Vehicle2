#pragma once

#include <Arduino.h>

// Za zadati interval u milisekundama, metoda IsTick() vraca true kada ovaj istekne.
class ItsTime
{
private:
    uint msInterval;
    uint cnt = 0;

public:
    // Konstruktor u koji treba proslediti interval (u milisekundama) na koji ce se izvrsavati neka akcija.
    ItsTime(uint msInterval) { this->msInterval = msInterval; }
    // Provera da li je vreme za neki redovni dogadjaj. U loop()-u : if (tim.IsTick()) DoSomething();
    bool IsTick();
};
