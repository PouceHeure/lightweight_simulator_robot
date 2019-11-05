#pragma once 

/**
 * @file interacter.hpp
 * @author Hugo POUSSEUR
 * @brief Definition Interacter class  
 * @version 0.1
 * @date 2019-10-31
 */

#include <string>

/**
 * @brief Interacter, entail like an interface
 * This interace is implemented by Subscriber and Publisher object  
 * 
 * @tparam T_MSG 
 */
template<typename T_MSG>
class Interacter {
    private: 
        std::string name;

    public: 
        /**
         * @brief Construct a new Interacter object
         * 
         * @param _name 
         */
        Interacter(std::string _name);

        /**
         * @brief Get the Topic Name object
         * 
         * @return std::string topic name attached to the current Interacter object
         */
        std::string getTopicName();
};

template<typename T_MSG>
Interacter<T_MSG>::Interacter(std::string _name):name(_name){}


template<typename T_MSG>
std::string Interacter<T_MSG>::getTopicName(){
    return this->name;
}

