#include "env/board.hpp"
#include "element/wall.hpp"

//! @cond Doxygen_Suppress

template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point){
    Point2D<int> current_point = emission_point; 
    updatePoint(direction,current_point);

    return this->spreadSignal(direction,emission_point,current_point);
}

template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point, Point2D<int> current_point){
    Cell* current_cell = getElementAt(this->matrix,current_point.getX(),current_point.getY());
    
    bool isTraversable = current_cell -> isTraversable();

    if(!isTraversable){
        updateSignalDirection(direction);
    }
    updatePoint(direction,current_point);
    if(emission_point == current_point){
        return 0;
    }
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
void Board<Cell>::updateAttractifScore(Cell* cell){
    Element* element = cell->getElement();
    if(element != nullptr){
        Point2D<int> coord = cell->getCoord();
        Point2D<int> point_begin = coord;
        Point2D<int> point_end = coord;
        int distance = 0;
        int score = element->computeFieldAttractive(distance);
        while(score > 0){
            for(int i=point_begin.getX();i<=point_end.getX();i++){
                for(int j = point_begin.getY();j<=point_end.getY();j++){
                    if(i > 0 && i < lines -1 && j > 0 && j < cols){
                        if(i == point_begin.getX() || i == point_end.getX() 
                        || j == point_begin.getY() || j == point_end.getY()){
                            matrix.at(i).at(j)->updateAttractifScore(score);
                       }
                    }
                }
            }
            point_begin.appendX(-1); point_begin.appendY(-1);
            point_end.appendX(+1); point_end.appendY(+1);
            score = element->computeFieldAttractive(++distance);
        }
    }
}

template<>
std::vector<std::vector<Cell*>> Board<Cell>::spreadDetection(int radius,Point2D<int> emission_point){
    std::vector<std::vector<Cell*>> elements;
    Point2D<int> begin_point = emission_point;
    begin_point.appendX(-radius);
    begin_point.appendY(-radius);
    Point2D<int> end_point = emission_point;
    end_point.appendX(+radius);
    end_point.appendY(+radius);

    //init map

    for(int i = 0; i < 2*radius + 1; i++)
    {
        std::vector<Cell*> v_cols_ptr(2*radius+1);
        elements.push_back(v_cols_ptr);
    }

    //update content 

    int i_elements = 0;
    int j_elements = 0;
    for(int i= begin_point.getX();i<=end_point.getX();i++){
        j_elements = 0;
        for(int j= begin_point.getY();j<=end_point.getY();j++){
            if(i >= 0 && i < lines && j >= 0 && j < cols){
                Cell* current_cell = getElementAt(matrix,i,j);
                elements.at(i_elements).at(j_elements) = current_cell;
            }
            j_elements++;
        }
        i_elements++;
    }
    return elements;
}

template<>
void Board<Cell>::displayAttractifField(){
    for(int i=0;i<lines;i++){
        for(int j=0;j<cols;j++){
            int score = matrix.at(i).at(j)->getAttractifScore() ;
            if(score == 0){
                std::cout << " ";
            }else{
                std::cout << score;
            }
        }
        std::cout << std::endl;
    }
}


//! @endcond