#include <Arduino.h>

const int pinMotorLeft1 = D5;
const int pinMotorLeft2 = D6;
const int delayInit = 5;
const int speedInit = PWMRANGE;
const int speed = 300;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, true);

  pinMode(pinMotorLeft1, OUTPUT);
  pinMode(pinMotorLeft2, OUTPUT);
  digitalWrite(pinMotorLeft1, false);
  digitalWrite(pinMotorLeft2, false);
}

void loop()
{
  delay(3000);

  analogWrite(pinMotorLeft1, speedInit);
  delay(delayInit);
  analogWrite(pinMotorLeft1, speed);
  digitalWrite(pinMotorLeft2, false);
  delay(1000);

  analogWrite(pinMotorLeft2, speedInit);
  delay(delayInit);
  digitalWrite(pinMotorLeft1, false);
  analogWrite(pinMotorLeft2, speed);
  delay(1000);

  digitalWrite(pinMotorLeft1, false);
  digitalWrite(pinMotorLeft2, false);
}