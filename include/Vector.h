#pragma once

// X i Y komponenta vektora kretanja vozila.
struct Vector
{
private:
    float x;               // Smer kretanja. 0 pravo, <0 ulevo, >0 udesno
    float y;               // Brzina kretanja. 0 stop, <0 unazad, >0 unapred
    const float min = -1; // minimalna vrednost za x i y
    const float max = 1;   // maksimalna vrednost za x i y

public:
    Vector()
    {
        x = 0;
        y = 0;
    }
    Vector(float x_, float y_)
    {
        SetX(x_);
        SetY(y_);
    }

    float GetX() { return x; }
    float GetY() { return y; }
    void SetX(float x_) { x = constrain(x_, min, max); }
    void SetY(float y_) { y = constrain(y_, min, max); }
    void Set(float x_, float y_)
    {
        SetX(x_);
        SetY(y_);
    }

    bool IsZero() { return x == 0 && y == 0; }
};