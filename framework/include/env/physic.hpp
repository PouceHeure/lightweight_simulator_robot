#pragma once 

#include "env/board.hpp"
#include "element/element.hpp"

enum Direction {
    north,
    est,
    west,
    south
};


class PhysicalPhenomenon {
        protected: 
            //const World<Element>* world;
        public: 
            PhysicalPhenomenon(); 
            virtual void Apply() = 0;
};