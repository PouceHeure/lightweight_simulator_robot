#pragma once

/**
 * @file subscriber.hpp
 * @author Hugo POUSSEUR
 * @brief Definition Subscriber class  
 * @version 0.1
 * @date 2019-10-31
 */

#include <communication/interacter.hpp>

#include <boost/bind.hpp>
#include <boost/function.hpp>

/**
 * @brief Subscribe to the the topic attached, once message is published in the topic, 
 * the subscriber gets the message
 * 
 * @tparam T_MSG type of message used
 */
template<typename T_MSG>
class Subscriber : public Interacter<T_MSG> {
    private: 
        boost::function<void(const T_MSG&)> callback;   
    public: 
        /**
         * @brief Construct a new Subscriber object
         * 
         * @param _name the topic name 
         * @param _callback the callback called at each data reception
         */
        Subscriber(std::string _name,boost::function<void(const T_MSG&)> _callback);

        /**
         * @brief Method called for trigging a new message
         * 
         * @param msg the data message 
         */
        void trigNewMsg(T_MSG msg);
};

template<typename T_MSG>
Subscriber<T_MSG>::Subscriber(std::string _name,boost::function<void(const T_MSG&)> _callback)
:callback(_callback),Interacter<T_MSG>(_name){
    
}

template<typename T_MSG>
void Subscriber<T_MSG>::trigNewMsg(T_MSG msg){
    callback(msg);
}
