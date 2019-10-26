#include "env/board.hpp"


template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point){
    Point2D<int> current_point = emission_point; 
    updateSignalPosition(direction,current_point);

    std::cout << "emission_point: " << emission_point.getX() << " " << emission_point.getY() << std::endl;
    std::cout << "current_point: " << current_point.getX() << " " << current_point.getY() << std::endl;
    return this->spreadSignal(direction,emission_point,current_point);
}

template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point, Point2D<int> current_point){
    Cell* current_cell = getElementAt(this->matrix,current_point.getX(),current_point.getY());
    
    std::cout << "- current_point: " << current_point.getX() << " " << current_point.getY() << std::endl;
    bool isTraversable = current_cell -> isTraversable();

    if(!isTraversable){
        updateSignalDirection(direction);
    }
    updateSignalPosition(direction,current_point);
    if(emission_point == current_point){
        return 0;
    }
    std::cout << "direction: " << direction << std::endl;
    return 1 + spreadSignal(direction,emission_point,current_point);

}