#pragma once 

#pragma once

#include <fstream>
#include "recorder/recorder.hpp"
#include "recorder/server.hpp"

template<typename T>
using CallbackRecorder =  boost::function<T(int,Board<Cell>*)>;

template<typename T>
class RecorderServer : public Recorder<T>{
    private: 
        Server* server;
        void init();

    public:
        RecorderServer(Server* _server, std::string _name,int _freq,CallbackRecorder<T> callback);
        RecorderServer(Server* _server, std::string _name, int _freq,T* var_to_listen);
        
        void treatmentData(int tick, T value);
};


template<typename T>
void RecorderServer<T>::init(){
    Recorder<T>::treatmentFunction = boost::bind(&RecorderServer<T>::treatmentData,this,_1,_2);
    server->advertiseNewRecorder(this);
}

template<typename T>
RecorderServer<T>::RecorderServer(Server* _server ,std::string _name, int _freq, CallbackRecorder<T> _callback)
:server(_server),Recorder<T>(_name,_freq,_callback){
   init();
}

template<typename T>
RecorderServer<T>::RecorderServer(Server* _server,std::string _name, int _freq, T* var_to_listen)
:server(_server),Recorder<T>(_name,_freq,var_to_listen){
   init();
}


template<typename T>
void RecorderServer<T>::treatmentData(int tick, T value){
    server->sendValue(this,tick,value);
}