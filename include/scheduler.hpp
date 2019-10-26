#pragma once 

#include <vector>
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
        std::vector<Robot> robots;
        bool isOk;
        Mode mode_current;
        boost::function<void(void)> mode_function;

        void modeAuto();
        void modeManuel();


    public:
        static unsigned int TIME_SLEEP_MS;

        Scheduler();

        void run();
        void attachMode(Mode mode);

};