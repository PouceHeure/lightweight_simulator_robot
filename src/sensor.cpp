#include "sensor/sensor.hpp"

Sensor::Sensor(int _freq,boost::function<void(void)> _callback):
freq(_freq),callback(_callback),power_current(Power::off){
    
}

void Sensor::switchPower(){
    switch(power_current){
        case Power::off:
            power_current = on;
            break;
        case Power::on:
            power_current = off;
            break;
    }
}