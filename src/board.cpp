#include "env/board.hpp"
#include "element/wall.hpp"


template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point){
    Point2D<int> current_point = emission_point; 
    updatePoint(direction,current_point);

    // std::cout << "emission_point: " << emission_point.getX() << " " << emission_point.getY() << std::endl;
    // std::cout << "current_point: " << current_point.getX() << " " << current_point.getY() << std::endl;
    return this->spreadSignal(direction,emission_point,current_point);
}

template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point, Point2D<int> current_point){
    Cell* current_cell = getElementAt(this->matrix,current_point.getX(),current_point.getY());
    
    // std::cout << "- current_point: " << current_point.getX() << " " << current_point.getY() << std::endl;
    bool isTraversable = current_cell -> isTraversable();

    if(!isTraversable){
        updateSignalDirection(direction);
    }
    updatePoint(direction,current_point);
    if(emission_point == current_point){
        return 0;
    }
    // std::cout << "direction: " << direction << std::endl;
    return 1 + spreadSignal(direction,emission_point,current_point);

}


template<>
bool Board<Cell>::moveRobot(Point2D<int> current, Point2D<int> target){
    Cell* target_cell = getElementAt(this->matrix,target.getX(),target.getY());
    Cell* current_cell = getElementAt(this->matrix,current.getX(),current.getY());

    if(target_cell == nullptr){
        return false;
    }

    bool target_is_free = target_cell -> isEmpty();
    if(target_is_free){
        Element* element = current_cell->detachElement();
        target_cell->attachElement(element); 
        // Wall* w = new Wall();
        // current_cell->attachElement(w);
    }
    return target_is_free;
}

template<>
std::vector<std::vector<Element*>> Board<Cell>::spreadDetection(int radius,Point2D<int> emission_point){
    std::vector<std::vector<Element*>> elements;
    Point2D<int> begin_point = emission_point;
    begin_point.appendX(-radius);
    begin_point.appendY(-radius);
    Point2D<int> end_point = emission_point;
    end_point.appendX(+radius);
    end_point.appendY(+radius);

    //init vector

    for(int i = 0; i < 2*radius + 1; i++)
    {
        std::vector<Element*> v_cols_ptr(2*radius+1);
        elements.push_back(v_cols_ptr);
    }

    int i_elements = 0;
    int j_elements = 0;
    for(int i= begin_point.getX();i<=end_point.getX();i++){
        j_elements = 0;
        for(int j= begin_point.getY();j<=end_point.getY();j++){
            if(i >= 0 && i < lines && j >= 0 && j < cols){
                Cell* current_cell = getElementAt(matrix,i,j);
                if(!current_cell->isEmpty()){
                    elements.at(i_elements).at(j_elements) = current_cell->getElement();
                }
            }
            j_elements++;
        }
        i_elements++;
    }
    return elements;
}
