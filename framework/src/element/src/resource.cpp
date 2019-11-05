#include "element/resource.hpp"


Resource::Resource():Element(){

}

char Resource::repr(){
    return Resource::REPR;
}

bool Resource::getIsTraversable(){
    return false;
}