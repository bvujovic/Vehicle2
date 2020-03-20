//* Testiranje motora koriscenjem Vector-a i MotorController-a.

// #include <Arduino.h>
// #include "MotorController.h"

// MotorController motors;

// void setup()
// {
//     Serial.begin(115200);
//     pinMode(LED_BUILTIN, OUTPUT);
//     digitalWrite(LED_BUILTIN, true);
//     delay(3000);

//     // test1: pravo, lagano
//     Vector v(0, 0.15);
//     motors.Go(v);
//     delay(3000);

//     // test2: skretanje ulevo
//     v.SetX(-0.9);
//     motors.Go(v);
//     delay(3000);

//     // test3: skretanje udesno 2x
//     v.SetX(0.5);
//     motors.Go(v, false);
//     v.SetX(0.5);
//     motors.Go(v);
//     delay(3000);

//     // test4: unazad
//     v.Set(0, -0.1);
//     motors.Go(v);
//     delay(5000);

//     // test5: unapred, max brzina
//     v.Set(0, 1);
//     motors.Go(v, false);
// }

// void loop()
// {
//     delay(3000);
// }