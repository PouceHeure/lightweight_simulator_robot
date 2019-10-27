#include "sensor/sensor.hpp"

ISensor::ISensor(int _freq):freq(_freq),power_current(Power::off){};


int ISensor::getFreq(){
    return this->freq;
}

Power ISensor::getPower(){
    return this->power_current;
}


void ISensor::switchPower(){
    switch(power_current){
        case Power::off:
            power_current = on;
            break;
        case Power::on:
            power_current = off;
            break;
    }
}

