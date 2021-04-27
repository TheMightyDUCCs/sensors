#ifndef TDS_H
#define TDS_H

#include "sensor.h"

// Example:
//
// void setup ()
// {
//     Serial.begin(115200);
// }
// void loop()
// {
//   TDS sen = TDS(A4); 
//   static unsigned long printTimepoint = millis();
//   if(millis()-printTimepoint > 800U)
//   {
//     printTimepoint = millis();
//     Serial.print("TDS Value:");
//     Serial.print(sen.read(),0);
//     Serial.println("ppm");
//   }
// }

class TDS : public Sensor {
    public:
        TDS(uint8_t pin);
        float read();
        void calibrate(float tds);
    private:
        uint8_t pin;
        float k_value;
        int getMedianNum(int bArray[], int iFilterLen);
};

#endif
