// #include <Arduino.h>

// /* This example shows how to get single-shot range
//  measurements from the VL53L0X. The sensor can optionally be
//  configured with different ranging profiles, as described in
//  the VL53L0X API user manual, to get better performance for
//  a certain application. This code is based on the four
//  "SingleRanging" examples in the VL53L0X API.

//  The range readings are in units of mm. */

// #include <Wire.h>
// #include <VL53L0X.h>

// VL53L0X sensor;
// #define HIGH_SPEED
// //#define HIGH_ACCURACY

// void setup()
// {
//   pinMode(LED_BUILTIN, OUTPUT);
//   digitalWrite(LED_BUILTIN, true);

//   Serial.begin(115200);
//   Wire.begin();

//   sensor.setTimeout(500);
//   if (!sensor.init())
//   {
//     Serial.println("Failed to detect and initialize sensor!");
//     while (1)
//       delay(1000);
//   }

// #if defined LONG_RANGE
//   // lower the return signal rate limit (default is 0.25 MCPS)
//   sensor.setSignalRateLimit(0.1);
//   // increase laser pulse periods (defaults are 14 and 10 PCLKs)
//   sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
//   sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
// #endif

// #if defined HIGH_SPEED
//   sensor.setMeasurementTimingBudget(20000); // reduce timing budget to 20 ms (default is about 33 ms)
// #elif defined HIGH_ACCURACY
//   sensor.setMeasurementTimingBudget(200000); // increase timing budget to 200 ms
// #endif
// }

// unsigned long ms;

// void loop()
// {
//   ms = millis();
//   uint16_t dist = sensor.readRangeSingleMillimeters();
//   Serial.print(millis() - ms);
//   Serial.print("\t\t");
//   Serial.print(dist);
//   if (sensor.timeoutOccurred())
//     Serial.print(" TIMEOUT");

//   Serial.println();
//   delay(500);
// }
