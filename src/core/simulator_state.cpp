#include "core/simulator_state.h"

// Constructor
SimulatorState::SimulatorState(const Program& program) : program(program) {}

void SimulatorState::reset(){
    registers.reset();
    memory.reset();
    stations.reset();
    cycle = 0;
    pc_index = 0;
}

// The simulation has finished if we've reached the last instruction in the program
bool SimulatorState::finished() const {
    return pc_index == int(program.size());
}

// The current instruction being executed
Instruction* SimulatorState::current_instruction(){
    return &(program.get(pc_index));
}

// Move to the next instruction in the program
void SimulatorState::advance_pc(){
    pc_index += 1;
}

// Jump to a specific instruction address (used for branches and jumps)
void SimulatorState::jump_to_address(int address){
    pc_index = address;
}