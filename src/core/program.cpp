#include "core/program.h"

void Program::add_instruction(const Instruction& inst){
    instructions.push_back(inst);
}

Instruction Program::get(int index) const{
    if (index < 0 || index >= size())
        throw std::out_of_range("Instruction index out of range");
    return instructions[index];
}

int Program::size() const{
    return int(instructions.size());
}

bool Program::empty() const{
    return instructions.empty();
}