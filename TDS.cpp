/***************************************************
 DFRobot Gravity: Analog TDS Sensor / Meter For Arduino
 <https://www.dfrobot.com/wiki/index.php/Gravity:_Analog_TDS_Sensor_/_Meter_For_Arduino_SKU:_SEN0244>

 Created 2017-8-22
 By Jason <jason.ling@dfrobot.com@dfrobot.com>

 GNU Lesser General Public License.
 See <http://www.gnu.org/licenses/> for details.
 All above must be included in any redistribution

 /***********Notice and Trouble shooting***************
 1. This code is tested on Arduino Uno and Leonardo with Arduino IDE 1.0.5 r2 and 1.8.2.
 2. More details, please click this link: <https://www.dfrobot.com/wiki/index.php/Gravity:_Analog_TDS_Sensor_/_Meter_For_Arduino_SKU:_SEN0244>
 ****************************************************/

#include <Arduino.h>
#include <TDS.h>

#define TdsSensorPin A1
#define VREF 5.0      // analog reference voltage(Volt) of the ADC
#define SCOUNT  30           // sum of sample point
int analogBuffer[SCOUNT];    // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,tmp = 25;

TDS::TDS(uint8_t pin)
{
    pinMode(pin, INPUT);
    this->pin = pin;
    this->k_value = 1.0; // default
    //this->calibrate();
}

float TDS::read() {
    float ecValue, ecValue25;
    for (int i = 0; i < SCOUNT; i++) //take SCOUNT samples
    {
        analogBuffer[i] = analogRead(this->pin); //read the analog value and store into the buffer
        delay(40);
    }   
    for(int i = 0; i < SCOUNT; i++)
       analogBufferTemp[i]= analogBuffer[i];
    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0; // read the analog value more stable by the median filtering algorithm, and convert to voltage value
    ecValue = (133.42 * averageVoltage * averageVoltage * averageVoltage - 255.86 * averageVoltage * averageVoltage + 857.39 * averageVoltage) * this->k_value;
    ecValue25 = ecValue / (1.0 + 0.02 * (tmp - 25.0));
    tdsValue = ecValue25 * 0.5;
    //float cmpCoefficient=1.0+0.02*(tmp-25.0); //tmp compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
    //float cmpVtg=averageVoltage/cmpCoefficient;  //tmp compensation
    //tdsValue=(133.42*cmpVtg*cmpVtg*cmpVtg - 255.86*cmpVtg*cmpVtg + 857.39*cmpVtg)*this->k_value; //convert voltage value to tds value
    return tdsValue;


    //this->analogValue = analogRead(this->pin);
    //this->voltage = this->analogValue / this->adcRange * this->aref;
    //this->ecValue = (133.42 * this->voltage * this->voltage * this->voltage - 255.86 * this->voltage * this->voltage + 857.39 * this->voltage) * this->kValue;
    //this->ecValue25 = this->ecValue / (1.0 + 0.02 * (this->temperature - 25.0)); //temperature compensation
    //this->tdsValue = ecValue25 * TdsFactor;
}

int TDS::getMedianNum(int bArray[], int iFilterLen) 
{
      int bTab[iFilterLen];
      for (byte i = 0; i<iFilterLen; i++)
      bTab[i] = bArray[i];
      int i, j, bTemp;
      for (j = 0; j < iFilterLen - 1; j++) 
      {
      for (i = 0; i < iFilterLen - j - 1; i++) 
          {
        if (bTab[i] > bTab[i + 1]) 
            {
        bTemp = bTab[i];
            bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
         }
      }
      }
      if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
      else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
      return bTemp;
}

void TDS::calibrate(float tds)
{   
    char cmdReceivedChar;
    char *cmdReceivedBufferPtr;
    float rawECsolution;
    // static unsigned long cmdReceivedTimeOut = millis();
    // Serial.print("Please enter the TDS value of the calibration solution into the terminal.");
    // while(Serial.available() == 0) {};
    // int tds = Serial.parseInt();
    for (int i = 0; i < SCOUNT; i++) //take SCOUNT samples
    {
        analogBuffer[i] = analogRead(this->pin); //read the analog value and store into the buffer
        delay(40);
    }   
    for(int i = 0; i < SCOUNT; i++)
       analogBufferTemp[i]= analogBuffer[i];
    averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0;
    rawECsolution = tds / 0.5;
    rawECsolution = rawECsolution * (1.0 + 0.02 * (tmp - 25.0));
    this->k_value = rawECsolution / (133.42 * averageVoltage * averageVoltage * averageVoltage - 255.86 * averageVoltage * averageVoltage + 857.39 * averageVoltage);
}
