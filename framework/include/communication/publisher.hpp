#pragma once 

/**
 * @file publisher.hpp
 * @author Hugo POUSSEUR
 * @brief Definition Publisher class  
 * @version 0.1
 * @date 2019-10-31
 */

#include <communication/topic.hpp>
#include <communication/interacter.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>


/**
 * @brief Publish message into the topic attached 
 * 
 * @tparam T_MSG the type message sent  
 */
template<typename T_MSG>
class Publisher : public Interacter<T_MSG>{
    private: 

        boost::function<void(T_MSG)> publishMsgToTopic;

    public: 
        /**
         * @brief Construct a new Publisher object
         * 
         * @param _name the topic name 
         */
        Publisher(std::string _name);

        /**
         * @brief Attach the method called at each message published 
         * @param method 
         */
        void attachPublishMethod(boost::function<void(T_MSG)> method);

        /**
         * @brief Method to call for publishing message 
         * 
         * @param msg 
         */
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
    if(publishMsgToTopic != NULL){
        publishMsgToTopic(msg);
    }
}
