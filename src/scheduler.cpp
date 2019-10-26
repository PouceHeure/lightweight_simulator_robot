#include <unistd.h>
#include <iostream>

#include "scheduler.hpp"

unsigned int Scheduler::TIME_SLEEP_MS = 1000; 

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
    while(isOk){
        std::cout << "bonjour" << std::endl;
        /* */
        mode_function();
    }    
}

