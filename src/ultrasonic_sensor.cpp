#include "sensor/ultrasonic_sensor.hpp"


UltrasonicSensor::UltrasonicSensor(int _freq,boost::function<void(int)> _callback,Direction _direction_watching)
:direction_watching(_direction_watching),Sensor<int>(_freq,_callback){

};      


void run(Board<Cell> &board){

}