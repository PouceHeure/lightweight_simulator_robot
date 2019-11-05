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
        boost::function<void(const T_MSG&)> callback;

        void attachCallBack(T_MSG* container);
        void callbackUpdateValue(T_MSG* container,const T_MSG& _value);

        Sensor(int _freq,boost::function<void(const T_MSG&)> _callback,T_MSG* _value);

    public: 
        Sensor(int _freq,boost::function<void(const T_MSG&)> _callback);
        Sensor(int _freq,T_MSG* _value);

        virtual void run(Board<Cell> &board,Point2D<int> &current_robot_position) = 0; 
        

};

template<typename T_MSG>
Sensor<T_MSG>::Sensor(int _freq,boost::function<void(const T_MSG&)> _callback):
Sensor<T_MSG>(_freq,_callback,nullptr){
    
}

template<typename T_MSG>
Sensor<T_MSG>::Sensor(int _freq,T_MSG* _value):
Sensor<T_MSG>(_freq,NULL,_value){
    
}

template<typename T_MSG>
Sensor<T_MSG>::Sensor(int _freq,boost::function<void(const T_MSG&)> _callback,T_MSG* container):
    callback(_callback),ISensor(_freq){
    attachCallBack(container);
}


template<typename T_MSG>
void Sensor<T_MSG>::callbackUpdateValue(T_MSG* container, const T_MSG& _value){
    *container = _value;
}


template<typename T_MSG>
void Sensor<T_MSG>::attachCallBack(T_MSG* container){
    if(callback.empty()){
        callback = boost::bind(&Sensor<T_MSG>::callbackUpdateValue,this,container,_1);
    }
}




