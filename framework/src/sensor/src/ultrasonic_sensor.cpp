#include "sensor/ultrasonic_sensor.hpp"


UltrasonicSensor::UltrasonicSensor(int _freq,int* _value,Direction _direction_watching)
:UltrasonicSensor(_freq,NULL,_value,_direction_watching){

};     


UltrasonicSensor::UltrasonicSensor(int _freq,boost::function<void(int)> _callback,Direction _direction_watching)
:UltrasonicSensor(_freq,_callback,NULL,_direction_watching){

};      


UltrasonicSensor::UltrasonicSensor(int _freq,boost::function<void(int)> _callback,int* _value,Direction _direction_watching)
:direction_watching(_direction_watching),Sensor<int>(_freq,_callback,_value){

};      



void UltrasonicSensor::run(Board<Cell> &board, Point2D<int> &current_position){
   int result = board.spreadSignal(direction_watching,current_position);
   this->callback(result);
}