#ifndef SENSOR_H
#define SENSOR_H

#include <vector>
#include <string>

// Update this enum to reflect newly supported sensors.
// Not sure if an enum is actually needed since we have to pass text
// up to user anyway.
/*enum SensorType { 
    DS18B20,
    TDS,
    pH,
    TURBIDITY
}; */

// In order to allow the phone application to remain uncoupled from the sensor class,
// we must provide a function which returns a text list to the app (an enum would have
// to be decoded), and we must be able to create an instance of a sensor based on the
// same text name when the user presses a button on the app. Currently, the constructor
// takes in the string. IDK if that's the best way to do it. It's just what seemed simplest
// to me. -Abbie 

class Sensor {
    public: 
        char * name;
        //SensorType sensor_type;
        uint8_t pin;
        //File * to_mem_location;
        //fprintf storage_format;
        unsigned int read_frequency;
        bool enable;
        void calibrate(float tds);

        static std::vector<std::string> get_available_sensors();
        virtual float read() = 0;
        static Sensor * create(char * stype, uint8_t pin, char * name);
        void set_read_frequency(unsigned int read_freq);
};

#endif
