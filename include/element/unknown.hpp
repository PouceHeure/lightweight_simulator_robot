#pragma once 

#include "element/element.hpp"


/**
 * @brief Unknonw element
 * 
 */
class Unknown : public Element {
    public: 
        static std::string NAME;
        static const char REPR = 'X';

        static const bool IS_TRAVERSABLE = false;

        Unknown();

        virtual char repr();
        virtual bool getIsTraversable();
};