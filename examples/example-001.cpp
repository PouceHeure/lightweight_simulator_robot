#include "env/board.hpp"
#include "scheduler.hpp"
#include "element/element.hpp"
#include "element/wall.hpp"
#include "env/cell.hpp"

#define NB_LINES 8 
#define NB_COLS 8

#define I_ROBOT 4
#define J_ROBOT 4 


int main(int argc,char** argv){
    Board<Cell>* board = Board<Cell>::getSingleton(NB_LINES,NB_COLS);

    Wall* as = new Wall();
    Robot* robot = new Robot("bob");
    board->fill();
    board->updateBorder(as);
    board->update(I_ROBOT,J_ROBOT,robot);
    board->display();

    std::cout << board->spreadSignal(Direction::north,Point2D<int>(I_ROBOT,J_ROBOT)) << std::endl;

    /*
    Element e; 
    board->update(0,0,&e);
    board->display();
    board->displaySave();

    Scheduler* scheduler = new Scheduler();
    scheduler->attachMode(Mode::automatic);
    scheduler->run();
    */

    return 0;
}