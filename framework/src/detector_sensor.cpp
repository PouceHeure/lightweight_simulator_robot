#include "sensor/detector_sensor.hpp"

DetectorSensor::DetectorSensor(int _freq,MatrixPtr* _value,int _radius)
:DetectorSensor(_freq,NULL,_value,_radius){

};     


DetectorSensor::DetectorSensor(int _freq,boost::function<void(MatrixPtr)> _callback,int _radius)
:DetectorSensor(_freq,_callback,NULL,_radius){

};      


DetectorSensor::DetectorSensor(int _freq,boost::function<void(MatrixPtr)> _callback,MatrixPtr* _value,int _radius)
:radius(_radius),Sensor<MatrixPtr>(_freq,_callback,_value){

};      

void DetectorSensor::run(Board<Cell> &board, Point2D<int> &current_position){
   MatrixPtr result = board.spreadDetection(this->radius,current_position);
   this->callback(result);
}