#pragma once 

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "env/board.hpp"

enum Power{
    on = 0,
    off
};

class ISensor{
    public:
     ISensor();
     virtual void run(Board<Cell> &board,Point2D<int> &current_robot_position) = 0; 
};

template<typename T_MSG>
class Sensor : public ISensor{
    protected:
        Power power_current;
        int freq;
        boost::function<void(T_MSG)> callback;

    public: 
        Sensor(int _freq,boost::function<void(const T_MSG&)> _callback);
        void switchPower();

        virtual void run(Board<Cell> &board,Point2D<int> &current_robot_position) = 0; 
};

template<typename T_MSG>
Sensor<T_MSG>::Sensor(int _freq,boost::function<void(const T_MSG&)> _callback):
freq(_freq),callback(_callback),power_current(Power::off){
    
}

template<typename T_MSG>
void Sensor<T_MSG>::switchPower(){
    switch(power_current){
        case Power::off:
            power_current = on;
            break;
        case Power::on:
            power_current = off;
            break;
    }
}