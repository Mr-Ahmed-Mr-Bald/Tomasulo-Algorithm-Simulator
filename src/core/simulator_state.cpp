#include "../../include/core/simulator_state.h"

SimulatorState::SimulatorState(const Program& program) : program(program){}

void SimulatorState::reset(){

}

bool SimulatorState::finished() const{

}

Instruction* SimulatorState::current_instruction(){

}

void SimulatorState::advance_pc(){
    pc_index += 1;
}

void SimulatorState::jump_to_address(int address){
    pc_index = address;
}