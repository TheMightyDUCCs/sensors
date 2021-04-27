#ifndef PH_H
#define PH_H

#include "sensor.h"

/*
* Example:
#include "pH.h"

void setup ()
{
    Serial.begin(115200);
}
void loop()
{
  pH sen = pH(A5); 
  static unsigned long printTimepoint = millis();
  if(millis()-printTimepoint > 1600U)
  {
    printTimepoint = millis();
    Serial.print("    pH:");  
    Serial.print(sen.read(),2);
    Serial.println(" ");
  }
}
*/

class pH : public Sensor {
    public:
        pH(uint8_t pin);
        float read();
    private:
        uint8_t pin;
};

#endif