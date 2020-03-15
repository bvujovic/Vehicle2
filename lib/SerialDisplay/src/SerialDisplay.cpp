#include "SerialDisplay.h"

void SerialDisplay::Println(String caption, LogicSpeeds ls)
{
    Serial.print(caption);
    Serial.print(": ");
    Serial.print(ls.r);
    Serial.print(", ");
    Serial.println(ls.l);
}

void SerialDisplay::Println(String caption, PWMs pwm)
{
    Serial.print(caption);
    Serial.print(": ");

    Serial.print(pwm.r1);
    Serial.print(", ");
    Serial.print(pwm.r2);
    
    Serial.print(" - ");
    
    Serial.print(pwm.l1);
    Serial.print(", ");
    Serial.println(pwm.l2);
}