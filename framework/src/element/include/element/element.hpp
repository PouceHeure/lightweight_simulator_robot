#pragma once 

/**
 * @file element.hpp
 * @author Hugo POUSSEUR
 * @brief Definition Element class 
 * @version 0.1
 * @date 2019-10-31
 */

#include <string>
#include <boost/function.hpp>

/**
 * @brief Defines set of objects that can be  
 * 
 */
class Element {
    private: 
        boost::function<int(int)> field_attractif;

    public: 
        static std::string TYPE;
        static const char REPR = '_';
        static const bool IS_TRAVERSABLE = false;

        Element();
        /**
         * @brief representation char  
         * 
         * @return char, return REPR static variable 
         */
        virtual char repr();

        /**
         * @brief Get the Is Traversable object, informing if the object 
         * can be traversable or not 
         *  
         * @return true the object can be traversable 
         * @return false the object can't be traversable 
         */
        virtual bool getIsTraversable();

        /**
         * @brief Compute the field attractive 
         * 
         * @return int 
         */
        virtual int computeFieldAttractive(int distance);

        void attachFieldAttractive(boost::function<int(int)> _field_attractif);
        
};