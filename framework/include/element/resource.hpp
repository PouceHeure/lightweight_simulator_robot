#pragma once

#include "element/element.hpp"

class Resource : public Element {
    public: 
        static std::string NAME;
        static const char REPR = '$';
        static const bool IS_TRAVERSABLE = true;

        Resource();

        virtual char repr();
        virtual bool getIsTraversable();
};