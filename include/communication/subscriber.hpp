#pragma once 

#include <communication/interacter.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>



template<typename T_MSG>
class Subscriber : public Interacter<T_MSG> {
    private: 
        boost::function<void(T_MSG)> callback;   
    public: 
        Subscriber(std::string _name,boost::function<void(T_MSG)> _callback);
        void trigNewMsg(T_MSG msg);
};

template<typename T_MSG>
Subscriber<T_MSG>::Subscriber(std::string _name,boost::function<void(T_MSG)> _callback)
:callback(_callback),Interacter<T_MSG>(_name){
    
}

template<typename T_MSG>
void Subscriber<T_MSG>::trigNewMsg(T_MSG msg){
    callback(msg);
}
