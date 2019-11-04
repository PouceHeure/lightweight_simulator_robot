#pragma once 

/**
 * @file board.hpp
 * @author Hugo POUSSEUR
 * @brief Definition Board class 
 * @version 0.1
 * @date 2019-10-31
 */

#include "utils/point2D.hpp"
#include "element/element.hpp"
#include "env/cell.hpp"
#include "env/physic.hpp"
#include "element/unknown.hpp"

#include <iostream>
#include <vector>

#include <cstdlib>
#include <iostream>
#include <ctime>


template<typename T> 
using  WorldPtr = std::vector<std::vector<T*>>;
template<typename T> 
using  World = std::vector<std::vector<T>>;

/**
 * @brief Represent the board, get information about containt 
 * It's a singleton class. 
 * 
 * The class is templated, allowing to adapt easily content of the world
 *   
 * 
 * @tparam T 
 */
template<typename T>
class Board{
    private: 
        static Board<T>* singleton;

        int lines;
        int cols; 
        WorldPtr<T> matrix;
        WorldPtr<T> matrix_save; 
        void displayMatrix(WorldPtr<T> _mat);
        T* getElementAt(WorldPtr<T> _mat, int i, int j);
        
        int spreadSignal(Direction direction,Point2D<int> emission_point, Point2D<int> current_point);
        void updateSignalDirection(Direction &direction);
       

        Board(int _width,int _height);

    public: 
        static Board<T>* getSingleton();
        static Board<T>* getSingleton(int _lines, int _cols); 
        
        /**
         * @brief Fill the world with the pointer given 
         * 
         * @param _value_ref
         */
        void fill(T* _value_ref);

        /**
         * @brief Fill the world with the default constructor of T
         * 
         */
        void fill();

        /**
         * @brief Add value_ref occurence times 
         * 
         * @param occurence 
         * @param value_ref 
         */
        void fillRandomOccur(int occurence,Element* value_ref);
        
        /**
         * @brief Add value_ref in fact the percent given 
         * 
         * @param percent 
         * @param value_ref 
         */
        void fillRandomPercent(float percent,Element* value_ref);
        

        /**
         * @brief Load world from file
         * /!\ not implemented yet /!\
         * 
         */
        void load();

        /**
         * @brief Save the current world in a second world 
         * 
         */
        void save();
        
        /**
         * @brief Update the current world, in attaching the element at i,j position 
         * 
         * @param i 
         * @param j 
         * @param value 
         */
        void update(int i,int j,Element* value);

        /**
         * @brief Update the current world, in attaching the value at i,j position 
         * 
         * @param i 
         * @param j 
         * @param value 
         */
        void update(int i,int j,T* value);

        /**
         * @brief Update the current world, in attaching the elment at point given  
         * 
         * @param position 
         * @param value 
         */
        void update(Point2D<int> position, Element* value);

        /**
         * @brief Update border of the current world with the element given 
         * 
         * @param value 
         */
        void updateBorder(Element* value);

        /**
         * @brief Update the point in fact the direction  
         * 
         * @param direction 
         * @param point 
         */
        void updatePoint(const Direction& direction,Point2D<int> &point);

        /**
         * @brief Update the attractif score of each cell in fact the cell given  
         * 
         * @param value 
         */
        void updateAttractifScore(T* value);

        /**
         * @brief Apply attractif methof of each element 
         * 
         */
        void updateAttractifScore();

        /**
         * @brief Display the world in terminal 
         * 
         */
        void display();

        /**
         * @brief Display attractif field of the world  
         * 
         */
        void displayAttractifField();

      
        void displaySave();

        const WorldPtr<T> getMatrix();

        /**
         * @brief Spread a signal inside the world 
         * 
         * @param direction 
         * @param emission_point 
         * @return int the number of cell throught 
         */
        int spreadSignal(Direction direction,Point2D<int> emission_point);
        
        /**
         * @brief Spread Detection signal from the emission_point given 
         * 
         * @param radius distance 
         * @param emission_point emission_point 
         * @return std::vector<std::vector<Cell*>> 
         */
        std::vector<std::vector<Cell*>> spreadDetection(int radius,Point2D<int> emission_point);
        bool moveRobot(Point2D<int> current, Point2D<int> target);

        
};

template<typename T>
Board<T>* Board<T>::singleton = nullptr;

template<typename T>
Board<T>* Board<T>::getSingleton(){
    if( singleton != nullptr){
        return singleton;
    }
    // may be catch an error 
    return nullptr;
}

template<typename T>
Board<T>* Board<T>::getSingleton(int _lines,int _cols){
    if(singleton == nullptr){
        singleton = new Board(_lines,_cols);
    }
    return singleton;
}


template<typename T>
Board<T>::Board(int _lines,int _cols):lines(_lines),cols(_cols){
    for(int i = 0; i < _lines; i++)
    {
        std::vector<T*> v_cols_ptr(_cols);
        this->matrix.push_back(v_cols_ptr);
        this->matrix_save.push_back(v_cols_ptr);
    }
};


template<typename T>
T* Board<T>::getElementAt(WorldPtr<T> _mat, int i, int j){
    return _mat.at(i).at(j);
}

template<typename T>
void Board<T>::fill(T* _value_ref){
    for(int i=0;i<this->lines;i++){
        for(int j=0;j<this->cols;j++){
            this->update(i,j,_value_ref);
        }
    }
}

template<typename T>
void Board<T>::fill(){
    for(int i=0;i<this->lines;i++){
        for(int j=0;j<this->cols;j++){
            auto coord = CREATE_POINT2D(i,j);
            T* new_element = new T(coord); 
            this->update(i,j,new_element);
        }
    }
}

template<typename T>
void Board<T>::displayMatrix(WorldPtr<T> _mat){
    for(int i=0;i<this->lines;i++){
        for(int j=0;j<this->cols;j++){
            std::cout << getElementAt(_mat,i,j)->repr();
        }
        std::cout << std::endl;
    }
}

template<typename T>
void Board<T>::display(){
    displayMatrix(this->matrix);
}

template<typename T>
void Board<T>::displaySave(){
    displayMatrix(this->matrix_save);
}

template<typename T>
void Board<T>::save(){
    for(int i=0;i<this->lines;i++){
        for(int j=0;j<this->cols;j++){
            this->matrix_save.at(i).at(j) = getElementAt(this->matrix,i,j);
        }
    }
}

template<typename T>
void Board<T>::update(int i,int j,T* _value){
    this->matrix.at(i).at(j) = _value;
}

template<typename T>
void Board<T>::update(int i,int j,Element* value){
    this->matrix.at(i).at(j)->attachElement(value);
}

template<typename T>
void Board<T>::update(Point2D<int> position,Element* value){
    this->update(position.getX(),position.getY(),value);
}

template<typename T>
void Board<T>::updateBorder(Element* value){
    for(int i=0;i<this->lines;i++){
        for(int j=0;j<this->cols;j++){
            if(i == this->lines-1 || i == 0){
                this->update(i,j,value);
            }
            else if(j == this->cols-1 || j == 0){
                this->update(i,j,value);
            }
        }
    }
}

template<typename T>
void Board<T>::updateAttractifScore(){
    for(int i=0;i<this->lines;i++){
        for(int j=0;j<this->cols;j++){
            updateAttractifScore(matrix.at(i).at(j));
        }
    }
}

template<typename T>
int Board<T>::spreadSignal(Direction direction,Point2D<int> emission_point, Point2D<int> current_point){
    
    return false; 
}

//! @cond

template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point, Point2D<int> current_point);


template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point);

//! @endcond

template<typename T>
void Board<T>::updateSignalDirection(Direction &direction){
     switch (direction)
        {
            case Direction::north:
                direction = Direction::south;
                break;

            case Direction::south:
                direction = Direction::north;
                break;

            case Direction::est:
                direction = Direction::west;
                break;

            case Direction::west:
                direction = Direction::est;
                break;
    }
}

template<typename T>
void Board<T>::updatePoint(const Direction& direction,Point2D<int> &point){
    switch (direction)
        {
            case Direction::north:
                point.appendX(-1);
                break;

            case Direction::south:
                point.appendX(+1);
                break;

            case Direction::est:
                point.appendY(+1);
                break;

            case Direction::west:
                point.appendY(-1);
                break;
    }
}

template<typename T>
void Board<T>::fillRandomOccur(int occurence,Element* value_ref){
    int cell_filled = 0;
    while(cell_filled < occurence){
        int randI = rand()%(this->lines -1) + 1;
        int randJ = rand()%(this->cols -1) + 1;
        //std::cout << "I: " << randI << "J: " << randJ << std::endl;
        if(getElementAt(this->matrix,randI,randJ)->isEmpty()){
            this->update(randI,randJ,value_ref);
            cell_filled++;
        }
    }
}

template<typename T>
void Board<T>::fillRandomPercent(float percent,Element* value_ref){
    int number_occur = (lines-2)*(cols-2)*percent;
    fillRandomOccur(number_occur,value_ref);
}



template<typename T>
const WorldPtr<T> Board<T>::getMatrix(){
    return this->matrix;
}


