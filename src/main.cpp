#include <Arduino.h>
#include "MotorController.h"

// const int pinMotorLeft1 = D5;
// const int pinMotorLeft2 = D6;
// const int delayInit = 5;  // vreme u ms za koje ce motor dobiti maksimalan impuls i to na pocetku kretanja
// const int speedMax = 750; // 2 18650 baterije daju max 8.2V, a motori rade na max 6V. Otuda je najveci PWM 750, ne 1023
// const int speed = 300;

MotorController motors;

void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, true);
    delay(3000);

    // test1: pravo, lagano
    Vector v(0, 0.5);
    motors.Go(v);
    delay(3000);

    // test2: skretanje ulevo
    v.SetX(-0.5);
    motors.Go(v);
    delay(3000);

    // test3: skretanje udesno 2x
    v.SetX(0.5);
    motors.Go(v);
    v.SetX(0.5);
    motors.Go(v);
    delay(3000);

    // test4: unazad
    v.Set(0, -0.5);
    motors.Go(v);
    delay(5000);

    // test5: unapred, max brzina
    v.Set(0, 1);
    motors.Go(v);
}

void loop()
{
    delay(3000);

    //   analogWrite(pinMotorLeft1, speedMax);
    //   delay(delayInit);
    //   analogWrite(pinMotorLeft1, speed);
    //   digitalWrite(pinMotorLeft2, false);
    //   delay(1000);

    //   analogWrite(pinMotorLeft2, speedMax);
    //   delay(delayInit);
    //   digitalWrite(pinMotorLeft1, false);
    //   analogWrite(pinMotorLeft2, speed);
    //   delay(1000);

    //   digitalWrite(pinMotorLeft1, false);
    //   digitalWrite(pinMotorLeft2, false);
}