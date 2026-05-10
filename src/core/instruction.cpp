#include "instruction.h"

int Instruction::get_index() const {
    return index;
}

std::string Instruction::get_raw_instruction() const{
    return raw_instruction;
}

Opcode Instruction::get_opcode() const{
    return opcode;
}

int Instruction::get_dest() const{
    return dest;
}

int Instruction::get_src1() const{
    return src1;
}

int Instruction::get_src2() const{
    return src2;
}

StageState Instruction::get_stage_state() const{
    return stage_state;
} 

InstructionTiming Instruction::get_timing() const{
    return timing;
}

void Instruction::set_stage_state(StageState state){
    stage_state = state;
}

void Instruction::set_timing(StageState state, int cycle){
    if(state == StageState::Issued)
        timing.issued = cycle;
    else if(state == StageState::Executing)
        timing.executing = cycle;
    else if(state == StageState::Finished)
        timing.finished = cycle;
    else if(state == StageState::Written)
        timing.written = cycle;
}