#pragma once 

#include <communication/topic.hpp>
#include <communication/interacter.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>



template<typename T_MSG>
class Publisher : public Interacter<T_MSG>{
    private: 
        boost::function<void(T_MSG)> publishMsgToTopic;

    public: 
        Publisher(std::string _name);
        void attachPublishMethod(boost::function<void(T_MSG)> method);
        void publish(T_MSG msg);
};

template<typename T_MSG>
Publisher<T_MSG>::Publisher(std::string _name)
:Interacter<T_MSG>(_name){
    
}

template<typename T_MSG>
void Publisher<T_MSG>::attachPublishMethod(boost::function<void(T_MSG)> method)
{
    publishMsgToTopic = method;
}


template<typename T_MSG>
void Publisher<T_MSG>::publish(T_MSG msg)
{
    publishMsgToTopic(msg);
}
