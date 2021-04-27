#include "DS18B20.h"
#include "TDS.h"
#include "pH.h"
#include "SEN0189.h"

using namespace std;

// Factory method to create objects of different types. 
// Change is required only in this function to create a new object type 
Sensor * Sensor::create(char * stype, uint8_t pin, char * name) { 
    if (stype == "DS18B20") 
        return new DS18B20(pin);
    else if (stype == "TDS") 
        return new TDS(pin);
    else if (stype == "pH") 
        return new pH(pin);
    else if (stype == "SEN0189") 
        return new SEN0189(pin);
    else return NULL; 
}

// Here is the list users may need to append to for new sensor support
std::vector<std::string> Sensor::get_available_sensors() {
    return {"DS18B20","TDS", "pH", "SEN0189"};
}

void Sensor::set_read_frequency(unsigned int freq)
{
    this->read_frequency = freq;
}

void Sensor::calibrate(float tds)
{
    return;
}

