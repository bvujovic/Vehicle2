#include "Wire.h"
#define TCAADDR 0x70
// #define TCAADDR 0x20

#include <VL53L0X.h>
VL53L0X sensor;

void tcaselect(uint8_t i)
{
    if (i > 7)
        return;
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << i);
    Wire.endTransmission();
}

void setup()
{
    Serial.begin(115200);
    Wire.begin();
    while (!Serial)
        delay(100);

    tcaselect(0);
    sensor.setTimeout(500);
    sensor.setMeasurementTimingBudget(20000);
    if (!sensor.init())
    {
        Serial.println("Failed to detect and initialize sensor 0");
        while (1)
            delay(100);
    }

    tcaselect(7);
    sensor.setTimeout(500);
    sensor.setMeasurementTimingBudget(20000);
    if (!sensor.init())
    {
        Serial.println("Failed to detect and initialize sensor 7");
        while (1)
            delay(100);
    }

    delay(100);
}

int i = 0;
unsigned long ms;
int iics[2] = {0, 7};

void loop()
{
    tcaselect(iics[i % 2]);

    ms = millis();
    uint16_t dist = sensor.readRangeSingleMillimeters();
    Serial.print(iics[i % 2]);
    Serial.print("\t");
    Serial.print(millis() - ms);
    Serial.print("\t");
    Serial.print(dist);
    if (sensor.timeoutOccurred())
        Serial.print(" TIMEOUT");

    i++;
    Serial.println();
    if (i % 2 == 0)
        Serial.println();
    delay(500);
}
