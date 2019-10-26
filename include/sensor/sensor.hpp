#pragma once 

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "env/board.hpp"

enum Power{
    on = 0,
    off
};

class ISensor{

};

template<typename T_MSG>
class Sensor : public ISensor{
    private:
        Power power_current;
        int freq;
        boost::function<void(int)> callback;

    public: 
        Sensor(int _freq,boost::function<void(const T_MSG&)> _callback);
        void switchPower();

        virtual void run(Board<Cell> board,Point2D<int> current_robot_position); 
};