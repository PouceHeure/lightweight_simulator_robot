#pragma once 

#include<string>

class Element {
    public: 
        static std::string TYPE;
        static const char REPR = '_';
        static const bool IS_TRAVERSABLE = false;

        Element();

        virtual char repr();
        virtual bool getIsTraversable();
        
};