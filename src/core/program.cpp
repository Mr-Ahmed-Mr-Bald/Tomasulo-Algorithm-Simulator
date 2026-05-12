#include "core/program.h"

// Add an instruction to the program
void Program::add_instruction(const Instruction& inst){
    instructions.push_back(inst);
}

// Get an instruction at a specific index in the program
const Instruction& Program::get(int index) const{
    if (index < 0 || index >= size())
        throw std::out_of_range("Instruction index out of range");
    return instructions[index];
}

// Get a mutable instruction at a specific index in the program
Instruction& Program::get(int index) {
    if (index < 0 || index >= size())
        throw std::out_of_range("Instruction index out of range");
    return instructions[index];
}

// Get an instruction by its memory address
const Instruction& Program::get_by_address(int address) const {
    if (!contains_address(address))
        throw std::out_of_range("Instruction address out of range");
    return instructions[address - start_address];
}

// Get a mutable instruction by its memory address
Instruction& Program::get_by_address(int address) {
    if (!contains_address(address))
        throw std::out_of_range("Instruction address out of range");
    return instructions[address - start_address];
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

int Program::get_end_address() const {
    return start_address + size();
}

bool Program::contains_address(int address) const {
    return address >= start_address && address < get_end_address();
}
