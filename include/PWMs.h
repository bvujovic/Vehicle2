#pragma once

// ...
struct PWMs
{
private:
    void Swap(float *pt1, float *pt2)
    {
        float temp = *pt1;
        *pt1 = *pt2;
        *pt2 = temp;
    }

public:
    float r1, r2; // PWM vrednosti za desni motor
    float l1, l2; // PWM vrednosti za levi motor

    void ReverseR() { Swap(&r1, &r2); }
    void ReverseL() { Swap(&l1, &l2); }

    void SetBrake() { r1 = r2 = l1 = l2 = 750; } // todo 750 ili PWMRANGE ili nesto trece???
    void SetStandby() { r1 = r2 = l1 = l2 = 0; }
};