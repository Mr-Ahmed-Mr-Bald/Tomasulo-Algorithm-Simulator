#include "../../include/core/program.h"

void Program::add_instruction(const Instruction& inst){
    instructions.push_back(inst);
}

Instruction& Program::get(int index){
    return instructions[index];
}

int Program::size() const{
    return instructions.size();
}

bool Program::empty() const{
    return instructions.empty();
}