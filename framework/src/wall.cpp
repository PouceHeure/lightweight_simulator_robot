#include "element/wall.hpp"


Wall::Wall():Element(){

}

char Wall::repr(){
    return Wall::REPR;
}

bool Wall::getIsTraversable(){
    return false;
}