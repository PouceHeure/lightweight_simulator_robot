#include "sensor/ultrasonic_sensor.hpp"


UltrasonicSensor::UltrasonicSensor(int _freq,boost::function<void(int)> _callback,Direction _direction_watching)
:direction_watching(_direction_watching),Sensor<int>(_freq,_callback){

};      


void UltrasonicSensor::run(Board<Cell> &board, Point2D<int> &current_position){
   int result = board.spreadSignal(direction_watching,current_position);
   this->callback(result);
}