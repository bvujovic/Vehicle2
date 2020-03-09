// #include <Arduino.h>

// const int pinMotorLeft1 = D1;
// const int pinMotorLeft2 = D2;
// const int speedInit = PWMRANGE;
// const int speed = 250;

// int freq = 30000;

// void setup()
// {
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, true);

//   pinMode(pinMotorLeft1, OUTPUT);
//   pinMode(pinMotorLeft2, OUTPUT);
// }

// void loop()
// {
//   delay(3000);

//   analogWrite(pinMotorLeft1, speedInit);
//   delay(5);
//   analogWrite(pinMotorLeft1, speed);
//   digitalWrite(pinMotorLeft2, false);
//   delay(1000);

//   analogWrite(pinMotorLeft2, speedInit);
//   delay(5);
//   digitalWrite(pinMotorLeft1, false);
//   analogWrite(pinMotorLeft2, speed);
//   delay(1000);

//   digitalWrite(pinMotorLeft1, false);
//   digitalWrite(pinMotorLeft2, false);

//   freq /= 2;
//   analogWriteFreq(freq);
// }