#include "../../include/core/simulator_state.h"

SimulatorState::SimulatorState(const Program& program) : program(program){}

void SimulatorState::reset(){

}

//the simulation has finished if we've reached the last instruction in the program
bool SimulatorState::finished() const{
    return pc_index == program.size();
}

//the current instruction being executed
Instruction* SimulatorState::current_instruction(){
    return &(program.get(pc_index));
}

void SimulatorState::advance_pc(){
    pc_index += 1;
}

void SimulatorState::jump_to_address(int address){
    pc_index = address;
}