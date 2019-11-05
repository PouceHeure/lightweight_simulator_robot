#pragma once 
#include <iostream>
#include <math.h>  

template<typename T>
class Point2D {
    private: 
        T x;
        T y;
    public: 
        static T CREATE(T _x,T _y);
        static float DIST(const Point2D<int>& pA,const Point2D<int>& pB);

        Point2D(T _x,T _y);
        T getX() const;
        T getY() const;

        void appendX(T value);
        void appendY(T value);

        float dist(const Point2D<int>& other_point) const;

        bool operator==(Point2D<T> &other_point);
        bool operator!=(Point2D<T> &other_point);

};

template<typename T>
Point2D<T> CREATE_POINT2D(T _x, T _y){
    return Point2D<T>(_x,_y);
}

template<typename T>
Point2D<T> DIST(const Point2D<int>& pA,const Point2D<int>& pB){
    return pA.dist(pB);
}

template<typename T>
Point2D<T>::Point2D(T _x,T _y){
    this->x = _x;
    this->y = _y;
} 

template<typename T>
T Point2D<T>::getX() const {
    return this->x;
} 

template<typename T>
T Point2D<T>::getY() const{
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

template<typename T>
bool Point2D<T>::operator!=(Point2D<T> &other_point){
    return !(*this == other_point);
} 


template<typename T>
float Point2D<T>::dist(const Point2D<int>& other_point) const{
    float distx = this->x - other_point.getX();
    float disty = this->y - other_point.getY();
    return sqrt(pow(distx,2)+pow(disty,2));
};