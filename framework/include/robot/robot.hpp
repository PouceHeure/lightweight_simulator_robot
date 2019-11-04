#pragma once 

#include <iostream>
#include <vector>
#include <queue>

#include "element/element.hpp"
#include "sensor/sensor.hpp"
#include "sensor/ultrasonic_sensor.hpp"
#include "instruction/move_instruction.hpp"


class Robot: public Element{

    static const char REPR = '0';
    static const bool IS_TRAVERSABLE = false;

    private: 
        static int COUNTER;
        int id;
        std::string name;

        const int speed_max = 2;

        std::vector<ISensor*> sensors;
        std::queue<MoveInstruction> instructions;
        std::vector<boost::function<void(void)>> callbacks;

        boost::function<void(Robot*,MoveInstruction*)> request_move_method;

    public:
        Robot(std::string _name);
        
        virtual char repr();
        virtual bool getIsTraversable();
        
        std::string getName();
        int getId();
        
        /**
         * @brief Method called at each tick 
         * 
         * @param ticks current tick simulation 
         * @param board board 
         * @param current_robot_position current position 
         */
        virtual void run(int ticks,Board<Cell> board,Point2D<int> current_robot_position);

        /**
         * @brief Add new intruction 
         * 
         * @param instruction 
         */
        void addInstruction(MoveInstruction instruction);

        /**
         * @brief 
         * 
         * @param sensor 
         */
        void attachSensor(ISensor* sensor);
        void attachCallBack(boost::function<void(void)>);

        void attachRequestMoveMethod(boost::function<void(Robot*,MoveInstruction*)> request);
        
        
};