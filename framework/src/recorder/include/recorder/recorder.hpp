#pragma once 

#include <vector>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include "env/board.hpp"

#define BUFFER_SIZE 10

class IRecorder {
    private: 
        std::string name;
    public: 
        IRecorder();
        IRecorder(std::string _name);
        virtual void record(int tick,Board<Cell>* board) = 0;
        std::string getName();
};

/**
 * Recorder allows to record some data during a simulation. 
 * These data allow to facility analyse.  
 */ 
template<typename T>
using CallbackRecorder =  boost::function<T(int,Board<Cell>*)>;

template<typename T>
class Recorder : public IRecorder{
    private:
        static const std::string UNKNOW_NAME; 
        int freq;
        CallbackRecorder<T> callback;

        T callbackListenVar(int tick,Board<Cell>* board,T* var_to_listen);
    
    protected:
        
        std::vector<std::pair<int,T>> containers;
        boost::function<void(int,T)> treatmentFunction;

    public:
        Recorder(int _freq,CallbackRecorder<T> _callback);
        Recorder(int _freq,T* var_to_listen);
        Recorder(std::string _name,int _freq,CallbackRecorder<T> _callback);
        Recorder(std::string _name,int _freq,T* var_to_listen);

        virtual void record(int tick,Board<Cell>* board);
};

template<typename T>
const std::string  Recorder<T>::UNKNOW_NAME = "UNKNOWN"; 

template<typename T>
Recorder<T>::Recorder(int _freq, CallbackRecorder<T> _callback)
:Recorder<T>(Recorder<T>::UNKNOW_NAME,_freq,_callback){

}

template<typename T>
Recorder<T>::Recorder(std::string _name, int _freq, CallbackRecorder<T> _callback)
:callback(_callback),freq(_freq),IRecorder(_name){

}

template<typename T>
Recorder<T>::Recorder(int _freq, T* var_to_listen):
Recorder<T>(Recorder<T>::UNKNOW_NAME,_freq,var_to_listen){
    
}

template<typename T>
Recorder<T>::Recorder(std::string _name, int _freq, T* var_to_listen):
freq(_freq),IRecorder(_name){
    callback = boost::bind(&Recorder<T>::callbackListenVar,this,_1,_2,var_to_listen);
}

template<typename T>
T Recorder<T>::callbackListenVar(int tick,Board<Cell>* board,T* var_to_listen){
    return *var_to_listen;
}

template<typename T>
void Recorder<T>::record(int tick,Board<Cell>* board)
{
    if(tick % freq == 0){
        // compute new value 
        T callback_value = callback(tick,board);
        // std::cout << callback_value << std::endl;
        // create couple with the current tick 
        std::pair<int,T> couple = std::make_pair(tick,callback_value);
        if(containers.size() == BUFFER_SIZE){
            containers.erase(containers.begin());
        }

        if(treatmentFunction != NULL){
            treatmentFunction(tick,callback_value);
        }

        containers.push_back(couple);

    }
}