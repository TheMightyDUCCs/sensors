#include <Arduino.h>
#include <pH.h>

#define Offset -30.00            //deviation compensate
#define LED 13
#define ArrayLength  40    //times of collection
int pHArray[ArrayLength];   //Store the average value of the sensor feedback
int pHArrayIndex=0;

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

pH::pH(uint8_t pin)
{
    pinMode(pin, INPUT);
    this->pin = pin;
}

float pH::read() {
    static float pHValue,voltage;

    for (int i = 0; i < ArrayLength; i++)
    {
        pHArray[pHArrayIndex++]=analogRead(this->pin);
        if(pHArrayIndex==ArrayLength)pHArrayIndex=0;
        delay(20);
    }   

    voltage = avergearray(pHArray, ArrayLength)*5.0/1024;
    pHValue = 3.5*voltage+Offset;
    return pHValue;
}


