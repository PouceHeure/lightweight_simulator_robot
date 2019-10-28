#include "robot/robot.hpp"

int Robot::COUNTER = 0;

Robot::Robot(std::string _name){
    this->name = _name;
    this->id = COUNTER;
    COUNTER++;
}

char Robot::repr(){
    return (char)(this->id+48);
}

bool Robot::getIsTraversable(){
    return false;
}

int Robot::getId(){
    return this->id;
}

std::string Robot::getName(){
    return this->name;
}

void Robot::run(int ticks, Board<Cell> board,Point2D<int> current_robot_position){
    //read sensors 
    std::vector<ISensor*>::iterator it_sensors;
    for (it_sensors = sensors.begin() ; it_sensors != sensors.end(); it_sensors++){
        if(ticks % (*it_sensors)->getFreq() == 0){
            (*it_sensors)->run(board,current_robot_position);
        }
    }

    //apply callbacks 
    std::vector<boost::function<void(void)>>::iterator it_cb;
    for(it_cb = callbacks.begin(); it_cb != callbacks.end(); it_cb++){
        (*it_cb)(); //call callback 
    }

    //apply instructions
    int nb_instructions_move = 0;
    while(!instructions.empty()){//} && nb_instructions_move < this->speed_max){
        MoveInstruction instruction = instructions.front();
        instructions.pop();
        request_move_method(this,&instruction);
        nb_instructions_move++;
    }

    //read sensors 
    //std::vector<ISensor*>::iterator it_sensors;
    // for (it_sensors = sensors.begin() ; it_sensors != sensors.end(); it_sensors++){
    //    (*it_sensors)->run(board,current_robot_position);
    // }

}

void Robot::attachCallBack(boost::function<void(void)> _callback){
    this->callbacks.push_back(_callback);
}

void Robot::addInstruction(MoveInstruction instruction){
    this->instructions.push(instruction);
}

void Robot::attachRequestMoveMethod(boost::function<void(Robot*,MoveInstruction*)> request){
    request_move_method = request;
}

void Robot::attachUltrasonicSensor(UltrasonicSensor* _ultrasonic_sensor){
    this->sensors.push_back(_ultrasonic_sensor);
}

void Robot::attachSensor(ISensor* sensor){
    this->sensors.push_back(sensor);
}
