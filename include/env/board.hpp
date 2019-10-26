#pragma once 

#include <iostream>
#include <vector>

#include "utils/point2D.hpp"
#include "element/element.hpp"
#include "env/cell.hpp"
#include "env/physic.hpp"

template<typename T> 
using  WorldPtr = std::vector<std::vector<T*>>;
template<typename T> 
using  World = std::vector<std::vector<T>>;

/**
 * Represent the board, get information about containt 
 * It's a singleton class 
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
        void updateSignalPosition(const Direction& direction,Point2D<int> &point);

        Board(int _width,int _height);

    public: 
        static Board<T>* getSingleton();
        static Board<T>* getSingleton(int _lines, int _cols); 
        
        void fill(T* _value_ref);
        void fill();
        void load();
        void save();
        
        void update(int i,int j,Element* _value);
        void update(int i,int j,T* _value);
        void updateBorder(Element* _value);
        
        void display();
        void displaySave();

        int spreadSignal(Direction direction,Point2D<int> emission_point);
        void moveRobot(Direction direction)

        
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
void Board<T>::update(int i,int j,Element* _value){
    this->matrix.at(i).at(j)->attachElement(_value);
}

template<typename T>
void Board<T>::updateBorder(Element* _value){
    for(int i=0;i<this->lines;i++){
        for(int j=0;j<this->cols;j++){
            if(i == this->lines-1 || i == 0){
                this->update(i,j,_value);
            }
            else if(j == this->cols-1 || j == 0){
                this->update(i,j,_value);
            }
        }
    }
}

template<typename T>
int Board<T>::spreadSignal(Direction direction,Point2D<int> emission_point, Point2D<int> current_point){
    
    return false; 
}

template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point, Point2D<int> current_point);


template<>
int Board<Cell>::spreadSignal(Direction direction,Point2D<int> emission_point);


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
void Board<T>::updateSignalPosition(const Direction& direction,Point2D<int> &point){
    switch (direction)
        {
            case Direction::north:
                point.appendX(-1);
                break;

            case Direction::south:
                point.appendX(+1);
                break;

            case Direction::est:
                point.appendY(-1);
                break;

            case Direction::west:
                point.appendY(+1);
                break;
    }
}



