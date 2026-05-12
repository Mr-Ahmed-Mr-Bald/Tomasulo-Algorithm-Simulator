#include "core/program.h"

// Add an instruction to the program
void Program::add_instruction(const Instruction& inst){
    instructions.push_back(inst);
}

// Get an instruction at a specific index in the program
Instruction Program::get(int index) const{
    if (index < 0 || index >= size())
        throw std::out_of_range("Instruction index out of range");
    return instructions[index];
}

// Get the total number of instructions in the program
int Program::size() const{
    return int(instructions.size());
}

// Check if the program has no instructions
bool Program::empty() const{
    return instructions.empty();
}

int Program::get_start_address() const {
    return start_address;
}