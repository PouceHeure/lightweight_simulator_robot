#pragma once 

#include "element/element.hpp"
#include "sensor/sensor.hpp"

using  MatrixPtr = std::vector<std::vector<Cell*>>;

class DetectorSensor : public Sensor<MatrixPtr> {
    private: 
        int radius; 
        DetectorSensor(int _freq,boost::function<void(MatrixPtr)> _callback,MatrixPtr* _value,int _radius);

    public:
        DetectorSensor(int _freq,boost::function<void(MatrixPtr)> _callback,int _radius);
        DetectorSensor(int _freq,MatrixPtr* _value,int _radius);
        
        virtual void run(Board<Cell> &board,Point2D<int> &current_position);
};