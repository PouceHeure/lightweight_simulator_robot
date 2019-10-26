#pragma once 

#include "env/physic.hpp"
#include "instruction/instruction.hpp"

struct MoveInstruction : public Instruction {
    public: 
        Direction direction;    
        int nb_cells; 
};