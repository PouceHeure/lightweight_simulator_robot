#pragma once 

#include "element/element.hpp"

class Wall : public Element {
    public: 
        static std::string NAME;
        static const char REPR = '#';

        static const bool IS_TRAVERSABLE = false;

        Wall();

        virtual char repr();
        virtual bool getIsTraversable();
};