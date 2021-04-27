#include <Arduino.h>
#include "SEN0189.h"

SEN0189::SEN0189(uint8_t pin)
{
    pinMode(pin, INPUT);
    this->pin = pin;
}

float SEN0189::read() {
    return analogRead(this->pin) * (1.0 / 1024.0);
}
