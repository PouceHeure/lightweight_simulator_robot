#include "robot/robot.hpp"

int Robot::COUNTER = 0;

Robot::Robot(std::string _name){
    this->name = _name;
    this->id = COUNTER;
    COUNTER++;
}

char Robot::repr(){
    return Robot::REPR;
}

bool Robot::getIsTraversable(){
    return false;
}

void Robot::run(Board<Cell> board,Point2D<int> current_robot_position){
    //read sensors 
    std::vector<ISensor>::iterator it_sensors;
    for (it_sensors = sensors.begin() ; it_sensors != sensors.end(); it_sensors++){
        //std::cout << ' ' << *it;
        //std::cout << '\n';
    }

    //apply callbacks 
    std::vector<boost::function<void(void)>>::iterator it_cb;
    for(it_cb = callbacks.begin(); it_cb != callbacks.end(); it_cb++){
        (*it_cb)(); //call callback 
    }

    //apply instructions
    int nb_instructions_move = 0;
    while(!instructions.empty && nb_instructions_move < this->speed_max){
        MoveInstruction instruction = instructions.front();
        instructions.pop();
        /* 
            apply instruction
        */
        nb_instructions_move++;
    }
}
