#include "env/cell.hpp"
#include <element/unknown.hpp>

Cell::Cell(Point2D<int> _coord):
attractif_score(0),coord(_coord),element(nullptr){}

Cell::Cell():Cell(Point2D<int>(-1,-1)){
    attachElement(new Unknown()); 
}

Element* Cell::getElement(){
    return this->element;
}

Point2D<int> Cell::getCoord(){
    return this->coord;
}

int Cell::getAttractifScore(){
    return this->attractif_score;
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

bool Cell::isEmpty(){
    return element == nullptr;
}

void Cell::updateAttractifScore(int _attractif_score)
{
    attractif_score += _attractif_score ;
}


