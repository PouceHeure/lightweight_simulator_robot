#include "env/cell.hpp"

Cell::Cell(Point2D<int> _coord):coord(_coord),element(nullptr){}

Element* Cell::getElement(){
    return this->element;
}

Element* Cell::detachElement(){
    Element* element_to_detach = getElement();
    this->element = nullptr;
    return element_to_detach;
}

bool Cell::attachElement(Element* _element){
    this->element = _element;
    return true; 
}

char Cell::repr(){
    // the cell is empty 
    if(element == nullptr){
        return Cell::REPR;
    }
    return this->element->repr();
}

bool Cell::isTraversable(){
    if(element == nullptr){
        return true;
    }
    return element->getIsTraversable();
}


