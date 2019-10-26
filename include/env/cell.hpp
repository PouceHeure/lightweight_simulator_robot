#pragma once 

#include "element/element.hpp"
#include "utils/point2D.hpp"

class Cell {
    static const char REPR = '_';

    private: 
        Point2D<int> coord;
        Element* element; 

    public: 
        Cell(Point2D<int> _coord);

        Element* getElement();
        Element* detachElement();
        bool attachElement(Element* _element);

        char repr();

        bool isTraversable();

        

};