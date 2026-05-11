#include "../../include/core/program.h"

void Program::add_instruction(const Instruction& inst){
    instructions.push_back(inst);
}

const Instruction& Program::get(int index) const{
    return instructions[index];
}

int Program::size() const{
    return instructions.size();
}

bool Program::empty() const{
    return instructions.empty();
}