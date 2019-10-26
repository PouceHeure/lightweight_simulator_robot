#include "env/physic.hpp"
#include "utils/point2D.hpp"



class Ultrasound: public PhysicalPhenomenon {
    private: 
    
        Direction direction;
        Point2D<int> from;

    public: 
        Ultrasound(Direction _direction, Point2D<int> _from);
        virtual void Apply();
};