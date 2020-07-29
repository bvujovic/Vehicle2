#include "RadioRecv.h"

int8_t RadioRecv::minPitch;
int8_t RadioRecv::maxAngle;
float RadioRecv::pitchInvCoef;

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
        // int8_t y = s[1];
        // Serial.print(x);
        // Serial.print('\t');
        // Serial.println(y);

        if (x > DrivingNormal) // da li se radi o spec kodovima (Spin, Pause, End...)
        {
            if (x == End) // End kôd: prekid radio komunikacije
                end();
            return (RadioRecvCode)x;
        }
        else
            return DrivingNormal;
    }
    else
        return None;
}

MotCmd *RadioRecv::getMotCmd()
{
    // pitch -> y (smer i brzina vozila)
    int8_t pitch = s[1];
    float y;
    if (abs(pitch) < minPitch)
        y = 0;
    else if (pitch > 0)
        y = map(pitch, minPitch, maxAngle, 0, 100) / pitchInvCoef;
    else
        y = map(pitch, -maxAngle, -minPitch, -100, 0) / pitchInvCoef;

    if (s[0] == DrivingSpin)
        return new MotCmd(y, 0, 500, Breaking);

    // roll -> x (pravac)
    float x = map((int8_t)s[0], -maxAngle, maxAngle, -100, 100) / 100.0F;

    if (y == 0)
        x = 0;

    // Serial.print(x);
    // Serial.print('\t');
    // Serial.println(y);

    if (x == 0 && y == 0 && xLast == 0 && yLast == 0) // nema potrebe za ponavljanjem 0,0 komande
        return NULL;
    xLast = x;
    yLast = y;

    return new MotCmd(x, y, 500, Breaking);
}
