#include "element/element.hpp"

Element::Element(){

}

/*Element::Element(const Element& element){
    Element e;
}*/

char Element::repr(){
    return Element::REPR;
}

bool Element::getIsTraversable(){
    return false;
}
