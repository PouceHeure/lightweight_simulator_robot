#include "recorder/recorder.hpp"


IRecorder::IRecorder(std::string _name):name(_name){

}

IRecorder::IRecorder(){

}

std::string IRecorder::getName(){
    return this->name;
}

