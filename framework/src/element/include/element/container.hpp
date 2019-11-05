#pragma once 

#include "element/element.hpp"

class Container : public Element {
    public: 
        static std::string NAME;
        static const char REPR = 'X';
        static const bool IS_TRAVERSABLE = false;

        Container();
        virtual char repr();
        virtual bool getIsTraversable();
};