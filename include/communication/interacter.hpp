#pragma once 

#include <string>
 
template<typename T_MSG>
class Interacter {
    private: 
        std::string name;

    public: 
        Interacter(std::string _name);
        std::string getTopicName();
};

template<typename T_MSG>
Interacter<T_MSG>::Interacter(std::string _name):name(_name){}

template<typename T_MSG>
std::string Interacter<T_MSG>::getTopicName(){
    return this->name;
}

