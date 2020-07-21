#include "RadioRecv.h"

RadioRecv::RadioRecv()
{
    rh = new RH_ASK(2000, 16, 12, 10, false);
}

RadioRecv::~RadioRecv()
{
    Serial.println("~RadioRecv");
}

bool RadioRecv::init()
{
    radioOn = rh->init();
    Serial.println(radioOn ? "RadioRecv Started" : "RadioRecv Init Failed!");
    return radioOn;
}

void RadioRecv::end()
{
    radioOn = false;
    // Serial.print("RadioRecv Resume: ");
    // Serial.println(rh->mode());
    rh->sleep();
    // Serial.println(rh->mode());
}

void RadioRecv::resume()
{
    radioOn = true;
    // Serial.print("RadioRecv Resume: ");
    // Serial.println(rh->mode());
    rh->available();
    // Serial.println(rh->mode());
}

RadioRecvCode RadioRecv::refresh()
{
    if (rh->recv(s, &n)) // Non-blocking
    {
        // driver.printBuffer("Got:", s, n);
        int8_t x = s[0];
        int8_t y = s[1];
        // Serial.print(x);
        // Serial.print('\t');
        // Serial.println(y);

        if (y == 0 && (x == End || x == Pause))
        {
            if (x == End) // End kôd: prekid radio komunikacije
                end();
            return (RadioRecvCode)x;
        }
        return WheelPos;
    }
    else
        return None;
}

MotCmd *RadioRecv::getMotCmd()
{
    const int8_t MAX_ANGLE = 45;
    const int8_t MIN_PITCH = 5;

    // pitch -> y (smer i brzina vozila)
    int8_t pitch = s[1];
    float y;
    if (abs(pitch) < MIN_PITCH)
        y = 0;
    else if (pitch > 0)
        y = map(pitch, MIN_PITCH, MAX_ANGLE, 0, 100) / 100.0F;
    else
        y = map(pitch, -MAX_ANGLE, -MIN_PITCH, -100, 0) / 100.0F;

    // roll -> x (pravac)
    float x = map((int8_t)s[0], -MAX_ANGLE, MAX_ANGLE, -100, 100) / 100.0F;

    // ako je y == 0, a cmdX veoma malo -> vozilo se ne krece
    // if (y == 0 && fabsf(x) < 0.2)
    //     x = 0;
    if (y == 0)
        if (fabsf(x) < 0.2)
            x = 0;
        else
        {
            //...
        }

    // Serial.print(x);
    // Serial.print('\t');
    // Serial.println(y);

    if (x == 0 && y == 0 && xLast == 0 && yLast == 0) // nema potrebe za ponavljanjem 0,0 komande
        return NULL;
    xLast = x;
    yLast = y;

    return new MotCmd(x, y, 500, Breaking);
}
