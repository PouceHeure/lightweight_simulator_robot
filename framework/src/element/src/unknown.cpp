#include "element/unknown.hpp"


Unknown::Unknown():Element(){

}

char Unknown::repr(){
    return Unknown::REPR;
}

bool Unknown::getIsTraversable(){
    return false;
}