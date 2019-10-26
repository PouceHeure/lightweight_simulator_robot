#pragma once 

#include <iostream>
#include <vector>
#include <queue>

#include "element/element.hpp"
#include "sensor/sensor.hpp"
#include "instruction/move_instruction.hpp"


class Robot: public Element{

    static const char REPR = '0';
    static const bool IS_TRAVERSABLE = false;

    private: 
        static int COUNTER;
        int id;
        std::string name;

        const int speed_max = 2;

        std::vector<ISensor> sensors;
        std::queue<MoveInstruction> instructions;
        std::vector<boost::function<void(void)>> callbacks;

    public:
        Robot(std::string _name);
        
        virtual char repr();
        virtual bool getIsTraversable();

        virtual void run(Board<Cell> board,Point2D<int> current_robot_position);

        //virtual void callbackSensors();
        
        
};