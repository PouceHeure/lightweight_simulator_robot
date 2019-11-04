#include "communication/publisher.hpp"
#include "communication/handle_communication.hpp"

#include "env/board.hpp"
#include "scheduler.hpp"
#include "element/resource.hpp"
#include "element/element.hpp"
#include "element/wall.hpp"
#include "env/cell.hpp"
#include "sensor/ultrasonic_sensor.hpp"
#include "sensor/detector_sensor.hpp"
#include "recorder/recorder_file.hpp"
#include "recorder/recorder_server.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>

#include <functional>
#include <iostream>

#include <recorder/server.hpp>

#define NB_LINES 15
#define NB_COLS 70

#define NB_ROBOTS 10
#define NB_ELEMENTS_RESOURCES 3
#define NB_ELEMENTS_WALLS 50 
#define COEFF_ATTRACTIVE_FIELD 6
#define SHOW_PERCEPTION false
#define SLEEP_MS 100


class MyRobot : public Robot {

    private: 
        int radius;
        int counter_detecter = 0;
        int ultrasonic_value;


        std::vector<std::vector<Cell*>> perception;
        boost::function<void(void)> callbackPerceptionGlobal;

        void callBackDetector(std::vector<std::vector<Cell*>> value,int radius){
            counter_detecter++;
            if(SHOW_PERCEPTION){
                std::cout << "robot:" << this->getName() << " perception:"<< std::endl;
                for(int i=0;i< 2*radius +1 ;i++){
                    std::cout << "               |";
                    for(int j=0;j< 2*radius +1 ;j++){
                        if(value.at(i).at(j) != nullptr){
                            std::cout << value.at(i).at(j)->repr();
                        }else{
                            std::cout << " ";
                        }
                        std::cout << "|";
                    }
                    std::cout << std::endl;
                }
            }
            perception = value;
            callbackPerceptionGlobal();
        }

    public:     
        MyRobot(std::string _name,int _radius)
        :radius(_radius),counter_detecter(0),ultrasonic_value(0),Robot(_name)
        {
             DetectorSensor* detectorSensor = new DetectorSensor(1,
                                    boost::bind(&MyRobot::callBackDetector,this,_1,_radius),
                                    _radius);
            this->attachSensor(detectorSensor);
            
            UltrasonicSensor* ultrasonicSensorNorth = new UltrasonicSensor(1,
                                    &ultrasonic_value,
                                    Direction::north);
            this->attachSensor(ultrasonicSensorNorth);
        }

        int getRadius(){
            return radius;
        }

        int* getCounterDetector(){
            return &this->counter_detecter;
        }

        int* getUltrasonicValue(){
            return &(this->ultrasonic_value);
        }

        std::vector<std::vector<Cell*>> getPerception(){
            return perception;
        }

        void attachGlobalPerceptionCallback(boost::function<void(void)> _callbackPerceptionGlobal){
            this->callbackPerceptionGlobal = _callbackPerceptionGlobal;
        }
};

struct RobotInfo {
    MyRobot* robot; 
    Point2D<int> position;
};

void callbackRobotMove(RobotInfo* robotInfo){
        if(robotInfo->robot->getPerception().size() == 0){
            return;
        }

        MoveInstruction move_instruction = MoveInstruction();
        move_instruction.nb_cells = 1;

        std::vector<std::vector<Cell*>> perception = robotInfo->robot->getPerception();
        int radius = robotInfo->robot->getRadius();

        std::vector<Direction> possibility;
        std::vector<std::pair<int,Direction>> map_scores;

        int scores = 0; 
        
        // north detection
        if(perception.at(radius-1).at(radius)->getElement() == nullptr){
            //std::cout << "north" << std::endl;
            possibility.push_back(north);
            int score = perception.at(radius-1).at(radius)->getAttractifScore();
            scores += score;
            map_scores.push_back(std::make_pair(score,north));
        }
        // south detection 
        if(perception.at(radius+1).at(radius)->getElement() == nullptr){
            //std::cout << "south" << std::endl;
            possibility.push_back(south);
            int score = perception.at(radius+1).at(radius)->getAttractifScore();
            scores += score;
            map_scores.push_back(std::make_pair(score,south));
        }
        // est detection 
        if(perception.at(radius).at(radius+1)->getElement() == nullptr){
            //std::cout << "est" << std::endl;
            possibility.push_back(est);
            int score = perception.at(radius).at(radius+1)->getAttractifScore();
            scores += score;
            map_scores.push_back(std::make_pair(score,est));
        }
        // west detection 
        if(perception.at(radius).at(radius-1)->getElement() == nullptr){
            //std::cout << "west" << std::endl;
            possibility.push_back(west);
            int score = perception.at(radius).at(radius-1)->getAttractifScore();            
            scores += score;
            map_scores.push_back(std::make_pair(score,west));
        }

        if(map_scores.size() != 0){
            int choice = std::rand()%2;
            if(scores == 0){
                int number_possibility = std::rand() % possibility.size();
                move_instruction.direction = possibility.at(number_possibility);
            }else{
                auto rng = std::default_random_engine {};
                std::shuffle(std::begin(map_scores), std::end(map_scores), rng);
                std::sort(map_scores.begin(), map_scores.end());
                move_instruction.direction = map_scores.at(map_scores.size() -1).second;
            }
            switch(move_instruction.direction){
                case north:
                    robotInfo->position.appendX(-1);
                    break;
                case south:
                    robotInfo->position.appendX(+1);
                    break;
                case est:
                    robotInfo->position.appendY(+1);
                    break;
                case west:
                    robotInfo->position.appendY(-1);
                    break;

            }
            robotInfo->robot->addInstruction(move_instruction);
        }else{
            //std::cout << "blocked" << std::endl;
        }

}

void callbackRobotPerception(RobotInfo* robotInfo,std::vector<std::vector<Cell*>>& world,int lines, int cols){
    int radius = robotInfo->robot->getRadius();
    std::vector<std::vector<Cell*>> perception = robotInfo->robot->getPerception();

    Point2D<int> point_begin = robotInfo->position;
    point_begin.appendX(-radius);
    point_begin.appendY(-radius);
    Point2D<int> point_end = robotInfo->position;
    point_end.appendX(+radius);
    point_end.appendY(+radius);

    int i_elements = 0;
    int j_elements = 0;
    for(int i= point_begin.getX();i<=point_end.getX();i++){
        j_elements = 0;
        for(int j= point_begin.getY();j<=point_end.getY();j++){
            if(i >= 0 && i < lines && j >= 0 && j < cols){
                world.at(i).at(j) = perception.at(i_elements).at(j_elements);
            }
            j_elements++;
        }
        i_elements++;
    }
}



/**
 * find the resource near of the robot given and compute the distance
 * between both 
 */ 
float findDistanceResourceNear(Board<Cell>* board,RobotInfo* robotInfo){
    std::vector<std::vector<Cell*>> matrix = board->getMatrix();
    std::vector<std::vector<Cell*>>::iterator it_lines; 
    std::vector<Cell*>::iterator it_cols; 

    float min_dist = -1;
    int i = 0;
    int j = 0;
    for(it_lines = matrix.begin(); it_lines != matrix.end(); ++it_lines){
        std::vector<Cell*> cols = *(it_lines);
        j = 0;
        for(it_cols = cols.begin(); it_cols != cols.end(); ++it_cols){
            Cell* cell = *it_cols;
            if(!cell->isEmpty()){
                Element* element = cell->getElement();
                if(dynamic_cast<Resource*>(element) != nullptr){
                    float current_dist = robotInfo->position.dist(Point2D<int>(i,j));
                    if(min_dist == -1 || current_dist < min_dist){
                        min_dist = current_dist;
                    }
                }
            }
            j++;
        }
        i++;
    } 
    return min_dist;
}

/**
 * @brief Init current representation, this representation will evoluted 
 * due to robots exploration
 * 
 * @param world 
 * @param lines 
 * @param cols 
 */
void worldInit(std::vector<std::vector<Cell*>>& world,int lines, int cols){
    for(int i = 0; i < lines; i++)
    {
        std::vector<Cell*> v_cols_ptr(cols);
        std::vector<Cell*>::iterator it;
        Unknown* unknown = new Unknown();
        for(it = v_cols_ptr.begin();it != v_cols_ptr.end();++it){
            (*it) = new Cell();
        } 
        world.push_back(v_cols_ptr);
    }
}

/**
 * @brief 
 * 
 * @param world 
 * @param lines 
 * @param cols 
 */
void worldDisplay(std::vector<std::vector<Cell*>>& world,int lines, int cols){
    for(int i=0;i<lines;i++){
        std::cout << "|";
        for(int j=0;j<cols;j++){
            if(world.at(i).at(j) != nullptr){
                std::cout << world.at(i).at(j)->repr();
            }else{
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}

float callbackRecorer(int ticks, Board<Cell> *board, std::vector<RobotInfo*>* robotinfos){
    float distance = 0;
    std::vector<RobotInfo*>::iterator it_ri;
    for(it_ri = robotinfos->begin();it_ri != robotinfos->end();++it_ri){
        distance += findDistanceResourceNear(board,*it_ri);
    } 
    return distance;
}

RobotInfo* addRobot(Scheduler* sc,std::vector<std::vector<Cell*>>& world,int id,int radius){
    // -2 + 1 avoid walls
    int i = std::rand() % (NB_LINES - 2) + 1;
    int j = std::rand() % (NB_COLS - 2) + 1;    
    
    struct RobotInfo* robotInfo = (struct RobotInfo*) malloc(sizeof(struct RobotInfo));

    std::string robot_name = "robot"+std::to_string(id);
    robotInfo -> robot = new MyRobot(robot_name,radius);
    robotInfo -> position = *(new Point2D<int>(i,j));

    boost::function<void(void)> callbackMoveBob = boost::bind(callbackRobotMove,robotInfo);
    boost::function<void(void)> callbackPerception = boost::bind(
                callbackRobotPerception,
                robotInfo,
                boost::ref(world),
                NB_LINES,NB_COLS);

    robotInfo->robot->attachGlobalPerceptionCallback(callbackPerception);
    robotInfo->robot->attachCallBack(callbackMoveBob);

    sc->addRobot(robotInfo->robot,robotInfo->position);

    return robotInfo;
}

int attractifFunction(int x){
    return COEFF_ATTRACTIVE_FIELD - x;
}

int main(int argc,char** argv){
    std::srand(std::time(nullptr));
    Board<Cell>* board = Board<Cell>::getSingleton(NB_LINES,NB_COLS);

    Scheduler::TIME_SLEEP_MS = SLEEP_MS;

    std::vector<RobotInfo*> robotinfos;

    Wall* wall = new Wall();
    Resource* resource = new Resource();
    resource->attachFieldAttractive(attractifFunction);
    board->fill();
    board->updateBorder(wall);
    board->fillRandomOccur(NB_ELEMENTS_WALLS,wall);
    board->fillRandomOccur(NB_ELEMENTS_RESOURCES,resource);
    board->updateAttractifScore();  

    std::vector<std::vector<Cell*>> world_perception;
    worldInit(world_perception,NB_LINES,NB_COLS);

    Scheduler* scheduler = new Scheduler();
    scheduler->attachMode(Mode::automatic);
    scheduler->attachBoard(board);

    Server* server = new Server(12345,"192.168.43.75");

    auto callbackWorldDisplay = boost::bind(worldDisplay,boost::ref(world_perception),NB_LINES,NB_COLS);
    scheduler->attachCallback(callbackWorldDisplay);

    int counter = 0;
    for(int i=0;i<NB_ROBOTS;i++){
        robotinfos.push_back(addRobot(scheduler,world_perception,counter,2));
        counter++;
    }

    // int a = 3;
    // RecorderServer<int>* recorder_ultrasonic = new RecorderServer<int>(server,"r_test_int",1,&a);//robotinfos.at(0)->robot->getUltrasonicValue());
    // scheduler->attachRecorder(recorder_ultrasonic);

    auto recorder_callback = boost::bind(&callbackRecorer,_1,_2,&robotinfos);
    RecorderFile<float>* recorder = new RecorderFile<float>(10,"test.csv",recorder_callback);
    scheduler->attachRecorder(recorder);

    int* counter_detector_ptr = robotinfos.at(0)->robot->getCounterDetector();
    RecorderFile<int>* recorder_ptr = new RecorderFile<int>(10,"test_ptr.csv",counter_detector_ptr);
    scheduler->attachRecorder(recorder_ptr);

    std::string bonjour = "bonjour";

    RecorderServer<float>* recorder_server = new RecorderServer<float>(server,"r_test_float",1,recorder_callback);
    scheduler->attachRecorder(recorder_server);

    RecorderServer<std::string>* recorder_server_str = new RecorderServer<std::string>(server,"r_test_str",1,&bonjour);
    scheduler->attachRecorder(recorder_server_str);
    
    scheduler->run();
    return 0;
}