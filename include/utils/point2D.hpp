#pragma once 
#include <iostream>

template<typename T>
class Point2D {
    private: 
        T x;
        T y;
    public: 
        static T CREATE(T _x,T _y);
        Point2D(T _x,T _y);
        T getX();
        T getY();

        void appendX(T value);
        void appendY(T value);

        bool operator==(Point2D<T> &other_point);

};

template<typename T>
Point2D<T> CREATE_POINT2D(T _x, T _y){
    return Point2D<T>(_x,_y);
}

template<typename T>
Point2D<T>::Point2D(T _x,T _y){
    this->x = _x;
    this->y = _y;
} 

template<typename T>
T Point2D<T>::getX(){
    return this->x;
} 

template<typename T>
T Point2D<T>::getY(){
    return this->y;
} 


template<typename T>
void Point2D<T>::appendX(T value){
    this->x += value;
} 

template<typename T>
void Point2D<T>::appendY(T value){
    this->y += value;
} 

template<typename T>
bool Point2D<T>::operator==(Point2D<T> &other_point){
    return this->x == other_point.getX() && this->y == other_point.getY();
} 