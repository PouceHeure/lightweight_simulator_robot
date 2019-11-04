#pragma once 

#include "element/element.hpp"
#include "utils/point2D.hpp"

class Cell {
    static const char REPR = '_';

    private: 
        Point2D<int> coord;
        Element* element;

        int attractif_score;

    public: 
        Cell();
        Cell(Point2D<int> _coord);

        Element* getElement();
        Point2D<int> getCoord();
        int getAttractifScore();

        Element* detachElement();
        bool attachElement(Element* _element);

        char repr();

        bool isTraversable();
        bool isEmpty();

        void updateAttractifScore(int attractif);
};