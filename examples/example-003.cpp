#include "communication/publisher.hpp"
#include "communication/handle_communication.hpp"

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
#include <iostream>

#define NB_LINES 15 
#define NB_COLS 30

#define I_ROBOT_BOB 6
#define J_ROBOT_BOB 6 

#define I_ROBOT_BIB 3
#define J_ROBOT_BIB 3


class MyRobot : public Robot {

    private: 

        Subscriber<int>* sub_ultra;
        Publisher<int>* pub_ultra;

        void callbackRobot(){
            MoveInstruction move_instruction = MoveInstruction();
            Direction new_direction = static_cast<Direction>(std::rand() % 4);
            move_instruction.direction = new_direction;
            move_instruction.nb_cells = 1;
            this->addInstruction(move_instruction);
        }

        void callBackSensor(int value,std::string _direction){
            std::cout << "robot:" << this->getName();
            std::cout << " id:" << this->getId();
            std::cout << " sensor:"  << _direction << ":" ; 
            std::cout << value << std::endl;

            pub_ultra->publish(value);
        }

        void callBackUltra(int value){
            std::cout << "robot:" << this->getName(); 
            std::cout << " received msg: " << value;
            std::cout << std::endl; 
        }

    public:     
        MyRobot(HandleCommunication &hc, std::string _name,std::string pub_topic,std::string sub_topic):Robot(_name)
        {
            // add callback robot  
            auto callback = std::bind(&MyRobot::callbackRobot,this);
            this->attachCallBack(callback);

            // attach ultrasonic 
            UltrasonicSensor* ultrasonicSensorNorth = new UltrasonicSensor(1,
                                    boost::bind(&MyRobot::callBackSensor,this,_1,"North"),
                                    Direction::north);
            this->attachUltrasonicSensor(ultrasonicSensorNorth);

            // attach publisher
            pub_ultra = hc.createPublisher<int>(pub_topic);

            // attach subscriber 
            sub_ultra = hc.createSubscriber<int>(sub_topic, boost::bind(&MyRobot::callBackUltra,this,_1));

        }
};


int main(int argc,char** argv){
    std::srand(std::time(nullptr));
    HandleCommunication* hc = new HandleCommunication();
    Board<Cell>* board = Board<Cell>::getSingleton(NB_LINES,NB_COLS);

    Wall* as = new Wall();
    board->fill();
    board->updateBorder(as);
    board->fillRandom(20,as);
    
    Scheduler* scheduler = new Scheduler();
    scheduler->attachMode(Mode::automatic);
    scheduler->attachBoard(board);
    scheduler->addRobot(new MyRobot(*hc,"bob","topic_0","topic_1"),Point2D<int>(I_ROBOT_BOB,J_ROBOT_BOB));
    scheduler->addRobot(new MyRobot(*hc,"bib","topic_1","topic_0"),Point2D<int>(I_ROBOT_BIB,J_ROBOT_BIB));

    scheduler->run();

    return 0;
}