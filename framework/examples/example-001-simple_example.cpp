#include "env/board.hpp"
#include "scheduler.hpp"
#include "element/element.hpp"
#include "element/wall.hpp"
#include "env/cell.hpp"
#include "sensor/ultrasonic_sensor.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>

#include <functional>

#define NB_LINES 15 
#define NB_COLS 30

#define I_ROBOT_BOB 6
#define J_ROBOT_BOB 6 

#define I_ROBOT_BIB 3
#define J_ROBOT_BIB 3

#define I_ROBOT_BAB 1
#define J_ROBOT_BAB 1

void callbackRobot(Robot* robot){
    MoveInstruction move_instruction = MoveInstruction();
    Direction new_direction = static_cast<Direction>(std::rand() % 4);
    move_instruction.direction = new_direction;
    move_instruction.nb_cells = 1;
    robot->addInstruction(move_instruction);
}

void callBackBreakLine(){
    std::cout << std::endl;
}

void callBackSensor(int value,Robot robot,std::string _direction){
    std::cout << "robot:" << robot.getName();
    std::cout << " id:" << robot.getId();
    std::cout << " sensor:"  << _direction << ":" ; 
    std::cout << value << std::endl;
}



Robot* createRobot(std::string name){
    Robot* robot = new Robot(name);
    auto callback = std::bind(callbackRobot,robot);
    robot->attachCallBack(callback);
    robot->attachCallBack(callBackBreakLine);

    UltrasonicSensor* ultrasonicSensorNorth = new UltrasonicSensor(1,
                                    boost::bind(callBackSensor,_1,*robot,"North"),
                                    Direction::north);
    robot->attachSensor(ultrasonicSensorNorth);

    UltrasonicSensor* ultrasonicSensorEst = new UltrasonicSensor(1,
                                    boost::bind(callBackSensor,_1,*robot,"Est"),
                                    Direction::est);
    robot->attachSensor(ultrasonicSensorEst);

    UltrasonicSensor* ultrasonicSensorWest = new UltrasonicSensor(1,
                                    boost::bind(callBackSensor,_1,*robot,"West"),
                                    Direction::west);
    robot->attachSensor(ultrasonicSensorWest);

    UltrasonicSensor* ultrasonicSensorSouth = new UltrasonicSensor(1,
                                    boost::bind(callBackSensor,_1,*robot,"South"),
                                    Direction::south);
    robot->attachSensor(ultrasonicSensorSouth);
    return robot;
}

int main(int argc,char** argv){
    std::srand(std::time(nullptr));
    Board<Cell>* board = Board<Cell>::getSingleton(NB_LINES,NB_COLS);

    Wall* as = new Wall();
    board->fill();
    board->updateBorder(as);
    board->fillRandomOccur(120,as);
    

    Scheduler* scheduler = new Scheduler();
    scheduler->attachMode(Mode::manuel);
    scheduler->attachBoard(board);
    scheduler->addRobot(createRobot("robot_bob"),Point2D<int>(I_ROBOT_BOB,J_ROBOT_BOB));
    scheduler->addRobot(createRobot("robot_bib"),Point2D<int>(I_ROBOT_BIB,J_ROBOT_BIB));
    scheduler->addRobot(createRobot("robot_bab"),Point2D<int>(I_ROBOT_BAB,J_ROBOT_BAB));
    scheduler->run();

    return 0;
}