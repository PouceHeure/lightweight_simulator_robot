#pragma once 

#include <vector>
#include <map>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <thread>
#include <chrono>

#include "env/board.hpp"
#include "element/element.hpp"
#include "robot/robot.hpp"

enum Mode {
    automatic = 0,
    manuel
};


class Scheduler {
    private: 
        Board<Cell>* board;
        std::map<Robot*,Point2D<int>> robots;
        bool isOk;
        Mode mode_current;
        boost::function<void(void)> mode_function;

        void modeAuto();
        void modeManuel();


    public:
        static unsigned int TIME_SLEEP_MS;

        Scheduler();

        //move this function 
        void addRobot(Robot* robot,Point2D<int> position);

        void run();
        void attachMode(Mode mode);
        void attachBoard(Board<Cell>* _board);

        void requestMoveRobot(Robot* robot, MoveInstruction* move_instruction);


};