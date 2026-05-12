#include "core/simulator_state.h"

// Constructor
SimulatorState::SimulatorState(const Program& program)
    : program(program), stations(memory) {
    reset();
}

void SimulatorState::reset(){
    registers.reset();
    memory.reset();
    stations.reset();
    cycle = 0;
    pc_index = program.get_start_address();
}

// The simulation has finished if we've reached the last instruction in the program
bool SimulatorState::finished() const {
    return !program.contains_address(pc_index);
}

// Move to the next instruction in the program
void SimulatorState::advance_pc(){
    pc_index += 1;
}

// Jump to a specific instruction address (used for branches and jumps)
void SimulatorState::jump_to_address(int address){
    pc_index = address;
}
