#pragma once

#include <MotorController.h>
#include <VTestsEnum.h>

// Klasa koja ce sadrzati metode kojima vozilo testira:
// Minimalne brzine (FWD/BCK, R/L) motora, balans motora za razlicite brzine kretanja...
class VTests
{
private:
    // Pokazivac na radni MotorController objekat kojem ce biti izdavane komande.
    static MotorController *motors;
    // Vreme startovanja tekuceg testa.
    static ulong msTestStart;
    // Vrsta tekuceg testa;
    static VTestsEnum testKind;

    static uint cntR, cntL;
    static void AddStatus(ulong msDur);    

public:
    // Preuzimanje reference na MotorController objekat. Poziv ove metode bi trebao biti u setup()-u.
    static void SetMotors(MotorController *m) { motors = m; }
    // Pokretanje testa.
    static void StartTest(VTestsEnum testKind, uint y);
    // Redovna provera testiranih parametara. Poziv ove metode bi trebao biti u loop()-u.
    static void Refresh(); 
};
