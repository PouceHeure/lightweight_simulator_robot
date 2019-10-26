#pragma once 

#include "sensor/sensor.hpp"
#include "env/physic.hpp"


class UltrasonicSensor : public Sensor<int> {
    private: 
        Direction direction_watching;
        
    public:
        UltrasonicSensor(int _freq,boost::function<void(int)> _callback,Direction _direction_watching);

        virtual void run(Board<Cell> &board,Point2D<int> &current_position);
};