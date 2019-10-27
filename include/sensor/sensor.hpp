#pragma once 

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "env/board.hpp"

enum Power{
    on = 0,
    off
};

class ISensor{
    protected: 
        Power power_current;
        int freq;

    public:
        ISensor(int _freq);

        Power getPower();
        int getFreq();

        void switchPower();
        virtual void run(Board<Cell> &board,Point2D<int> &current_robot_position) = 0; 
};

template<typename T_MSG>
class Sensor : public ISensor{
    protected:
        boost::function<void(T_MSG)> callback;

    public: 
        Sensor(int _freq,boost::function<void(const T_MSG&)> _callback);
         
        virtual void run(Board<Cell> &board,Point2D<int> &current_robot_position) = 0; 
};

template<typename T_MSG>
Sensor<T_MSG>::Sensor(int _freq,boost::function<void(const T_MSG&)> _callback):
callback(_callback),ISensor(_freq){
    
}
