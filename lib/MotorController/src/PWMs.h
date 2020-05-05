#pragma once

// ...
struct PWMs
{
private:
    //todo mozda ovo moze da se izbaci iz klase i umesto toga da se koristi SWAP iz Utils
    void Swap(float *pt1, float *pt2)
    {
        float temp = *pt1;
        *pt1 = *pt2;
        *pt2 = temp;
    }

public:
    //todo odluciti sta tacno sadrze ova polja: pwm vrednosti 0-pwmrange (short) ili su to koeficijenti 0-1 (float)
    float r1, r2; // PWM vrednosti za desni motor
    float l1, l2; // PWM vrednosti za levi motor

    PWMs() { SetStandby(); }
    PWMs(float r1, float r2, float l1, float l2)
    {
        this->r1 = r1;
        this->r2 = r2;
        this->l1 = l1;
        this->l2 = l2;
    }

    void ReverseR() { Swap(&r1, &r2); }
    void ReverseL() { Swap(&l1, &l2); }

    void SetBrake() { r1 = r2 = l1 = l2 = 750; }
    void SetStandby() { r1 = r2 = l1 = l2 = 0; }
};