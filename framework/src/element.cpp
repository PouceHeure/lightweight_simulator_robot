#include "element/element.hpp"

Element::Element(){

}


char Element::repr(){
    return Element::REPR;
}

bool Element::getIsTraversable(){
    return false;
}

int Element::computeFieldAttractive(int d){
    if( field_attractif != NULL){
        return field_attractif(d);
    }
    return 0;
}

void Element::attachFieldAttractive(boost::function<int(int)> _field_attractif){
    this->field_attractif = _field_attractif;
}
