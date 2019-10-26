#pragma once 

#include "env/physic.hpp"
#include "instruction/instruction.hpp"

class MoveInstruction : public Instruction {
    Direction direction;    
    int nb_cells; 
};