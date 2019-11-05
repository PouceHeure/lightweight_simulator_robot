#pragma once

#include <fstream>
#include "recorder/recorder.hpp"

template<typename T>
using CallbackRecorder =  boost::function<T(int,Board<Cell>*)>;

template<typename T>
class RecorderFile : public Recorder<T>{
    private: 
        std::string file_path;
        std::fstream file;
    public:
        RecorderFile(int _freq, std::string _file_path,CallbackRecorder<T> callback);
        RecorderFile(int _freq, std::string _file_path,T* var_to_listen);
        void treatmentData(int tick, T value);
};


template<typename T>
RecorderFile<T>::RecorderFile(int _freq, std::string _file_path, CallbackRecorder<T> _callback)
:file_path(_file_path),Recorder<T>(_freq,_callback){
    Recorder<T>::treatmentFunction = boost::bind(&RecorderFile<T>::treatmentData,this,_1,_2);
}

template<typename T>
RecorderFile<T>::RecorderFile(int _freq, std::string _file_path, T* var_to_listen)
:file_path(_file_path),Recorder<T>(_freq,var_to_listen){
    Recorder<T>::treatmentFunction = boost::bind(&RecorderFile<T>::treatmentData,this,_1,_2);
}


template<typename T>
void RecorderFile<T>::treatmentData(int tick, T value){
    file.open(file_path,std::ios::app);
    if(file.is_open()){
        file << tick << ";";
        file << value;
        file << std::endl;
        file.close();
    }
}