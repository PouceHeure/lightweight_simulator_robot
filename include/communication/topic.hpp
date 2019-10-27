#pragma once 

#include <string>
#include <vector>

#include "communication/subscriber.hpp"
#include "communication/interacter.hpp"

class ITopic {
    private: 
        std::string name;
    public: 
        ITopic(std::string _name);
};

template<typename T_MSG>
class Topic : public ITopic {
    
    private: 
        T_MSG* msg;
        std::vector<Subscriber<T_MSG>> subscribers;

    public: 
        Topic(std::string _name);
        void addSubscriber(Subscriber<T_MSG> subscriber);
        void broadcast(T_MSG msg);

};

template<typename T_MSG>
Topic<T_MSG>::Topic(std::string _name):ITopic(_name){}

template<typename T_MSG>
void Topic<T_MSG>::broadcast(T_MSG msg){
    typename std::vector<Subscriber<T_MSG>>::iterator it_sub;
    for(it_sub = subscribers.begin(); it_sub != subscribers.end(); ++it_sub){
        (*it_sub).trigNewMsg(msg);
    }
}

template<typename T_MSG>
void Topic<T_MSG>::addSubscriber(Subscriber<T_MSG> subscriber){
    subscribers.push_back(subscriber);
}


