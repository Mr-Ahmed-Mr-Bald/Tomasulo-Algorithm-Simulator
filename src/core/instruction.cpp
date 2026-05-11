#include "../../include/core/instruction.h"

Instruction::Instruction(int index, Opcode opcode, int dest, int src1, int src2, const std::string& raw_instruction) :
        index(index), dest(dest), src1(src1), src2(src2), raw_instruction(raw_instruction){}

//instruction index
int Instruction::get_index() const {
    return index;
}

//raw string instruction
std::string Instruction::get_raw_instruction() const{
    return raw_instruction;
}

//instructions' opcode
Opcode Instruction::get_opcode() const{
    return opcode;
}

//instruction's destination address
int Instruction::get_dest() const{
    return dest;
}

//instruction's src1 address
int Instruction::get_src1() const{
    return src1;
}

//instruction's src2 address
int Instruction::get_src2() const{
    return src2;
}

//instruction's stage state
StageState Instruction::get_stage_state() const{
    return stage_state;
} 

//instruction's timing
InstructionTiming Instruction::get_timing() const{
    return timing;
}

//set instruction stage state to specific value
void Instruction::set_stage_state(StageState state){
    stage_state = state;
}

//set timing of a particular state to a particular value (cycle)
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