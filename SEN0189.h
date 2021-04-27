#ifndef SEN0189_H
#define SEN0189_H

#include "sensor.h"

/*
* Example:
#include "SEN0189.h"

void setup ()
{
    Serial.begin(115200);
}
void loop()
{
  SEN0189 sen = SEN0189(A5); 
  static unsigned long printTimepoint = millis();
  if(millis()-printTimepoint > 1600U)
  {
    printTimepoint = millis();
    Serial.print("    Trubidity value: ");
    Serial.print(sen.read(),2);
    Serial.println(" ");
  }
}
*/

class SEN0189 : public Sensor {
    public:
        SEN0189(uint8_t pin);
        float read();
    private:
        uint8_t pin;
};

#endif