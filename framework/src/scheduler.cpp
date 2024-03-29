#include <unistd.h>
#include <iostream>

#include "scheduler.hpp"

unsigned int Scheduler::TIME_SLEEP_MS = 30; 

Scheduler::Scheduler():isOk(true){


}
void Scheduler::modeAuto(){
   auto sleep_duration = std::chrono::milliseconds(Scheduler::TIME_SLEEP_MS);
   std::this_thread::sleep_for(sleep_duration); 
}

void Scheduler::modeManuel(){
    std::cout << "Press Enter to continue" << std::endl;
    std::cin.ignore();
}

void Scheduler::attachMode(Mode mode){
    this->mode_current = mode;
    switch(mode){
            case automatic:
                mode_function = boost::bind(&Scheduler::modeAuto,this);
                break;
            case manuel:
                mode_function = boost::bind(&Scheduler::modeManuel,this);
                break;
    }
}

void Scheduler::run(){
    if(mode_function == nullptr){
        throw std::invalid_argument("Mode isn't attached !");
    }
    int ticks = 0;
    while(isOk){
        std::system("clear");
        std::cout << ticks << std::endl;
        //display current map:
        std::cout << "MAP REFERENCE" << std::endl;
        board->display();
        std::cout << "MAP ATTRACTIF FIELD" << std::endl;
        board->displayAttractifField();
        std::cout << "MAP CREATED" << std::endl;
        std::map<Robot*,Point2D<int>>::iterator it_robot;
        for(it_robot = robots.begin();it_robot != robots.end();++it_robot){
            it_robot->first->run(ticks,*board,it_robot->second);
        }
        std::vector<boost::function<void(void)>>::iterator it_cb;
        for(it_cb = callbacks.begin();it_cb != callbacks.end();++it_cb){
            (*it_cb)();
        }

        std::vector<IRecorder*>::iterator it_recorder;
        for(it_recorder = recorders.begin();it_recorder != recorders.end();++it_recorder){
            (*it_recorder)->record(ticks,this->board);
        }

        mode_function();
        ticks++; //update clock 
    }    
}

void Scheduler::requestMoveRobot(Robot* robot, MoveInstruction* move_instruction){
    Point2D<int> get_current_position = this->robots.at(robot);
    int nb_cells_through = 0;
    bool is_blocked = false; 
    do{
        Point2D<int> new_position = get_current_position;
        this->board->updatePoint(move_instruction->direction,new_position);
        is_blocked = !this->board->moveRobot(get_current_position,new_position);
        if(!is_blocked){
            get_current_position = new_position;
            nb_cells_through++;
        }
    }while(nb_cells_through < move_instruction->nb_cells && !is_blocked);
    robots.at(robot) = get_current_position;
}

void Scheduler::addRobot(Robot* robot, Point2D<int> position){
    robot->attachRequestMoveMethod(boost::bind(&Scheduler::requestMoveRobot,this,_1,_2));
    robots.insert({robot, position});
    board->update(position,robot);
}


void Scheduler::attachBoard(Board<Cell>* _board){
    this->board = _board;
}

void Scheduler::attachCallback(boost::function<void(void)> _callback){
    callbacks.push_back(_callback);
}


void Scheduler::attachRecorder(IRecorder* _recorder){
    recorders.push_back(_recorder);
}


