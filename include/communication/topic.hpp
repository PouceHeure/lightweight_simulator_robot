#pragma once 

/**
 * @file topic.hpp
 * @author Hugo POUSSEUR
 * @brief Definition ITopic interface and Topic class  
 * @version 0.1
 * @date 2019-10-31
 */

#include <string>
#include <vector>

#include "communication/subscriber.hpp"
#include "communication/interacter.hpp"

/**
 * @brief Interface topic, this interface allows to store Topic<T_MSG> object easilly
 * 
 */
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
        /**
         * @brief Construct a new Topic object
         * 
         * @param _name the topic name 
         */
        Topic(std::string _name);
        
        /**
         * @brief Add subscriber that listen the topic 
         * 
         * @param subscriber 
         */
        void addSubscriber(Subscriber<T_MSG> subscriber);

        /**
         * @brief Broadcast message received to all subscribers  
         * 
         * @param msg message received 
         */
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


