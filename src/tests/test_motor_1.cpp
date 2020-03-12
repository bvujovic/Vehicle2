// #include <Arduino.h>

// const int pinMotorLeft1 = D5;
// const int pinMotorLeft2 = D6;
// const int delayInit = 5;  // vreme u ms za koje ce motor dobiti maksimalan impuls i to na pocetku kretanja
// const int speedMax = 750; // 2 18650 baterije daju max 8.2V, a motori rade na max 6V. Otuda je najveci PWM 750, ne 1023
// const int speed = 300;

// void setup()
// {
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, true);

//   pinMode(pinMotorLeft1, OUTPUT);
//   pinMode(pinMotorLeft2, OUTPUT);
//   digitalWrite(pinMotorLeft1, false);
//   digitalWrite(pinMotorLeft2, false);
// }

// void loop()
// {
//   delay(3000);

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
// }