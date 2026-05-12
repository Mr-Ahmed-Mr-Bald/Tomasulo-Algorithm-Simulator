#include "core/enums.h"
#include "core/instruction.h"

Instruction::Instruction(
    int index,
    Enums::Opcode opcode,
    int dest,
    int src1,
    int src2,
    const std::string& raw_instruction
) : index(index),
    dynamic_id(-1),
    raw_instruction(raw_instruction),
    opcode(opcode),
    dest(dest),
    src1(src1),
    src2(src2),
    stage_state(Enums::StageState::Waiting) {}

// Instruction index
int Instruction::get_index() const {
    return index;
}

// Dynamic instruction issue order
int Instruction::get_dynamic_id() const {
    return dynamic_id;
}

// Raw string instruction
std::string Instruction::get_raw_instruction() const {
    return raw_instruction;
}

// Instructions' opcode
Enums::Opcode Instruction::get_opcode() const {
    return opcode;
}

// Instruction's destination address
int Instruction::get_dest() const {
    return dest;
}

// Instruction's src1 address
int Instruction::get_src1() const {
    return src1;
}

// Instruction's src2 address
int Instruction::get_src2() const {
    return src2;
}

// Instruction's stage state
Enums::StageState Instruction::get_stage_state() const {
    return stage_state;
} 

// Instruction's timing
InstructionTiming Instruction::get_timing() const {
    return timing;
}

// Set dynamic issue order
void Instruction::set_dynamic_id(int id) {
    dynamic_id = id;
}

// Set instruction stage state to specific value
void Instruction::set_stage_state(Enums::StageState state){
    stage_state = state;
}

// Set timing of a particular state to a particular value (cycle)
void Instruction::set_timing(Enums::StageState state, int cycle){
    if (state == Enums::StageState::Issued)
        timing.issued = cycle;
    else if (state == Enums::StageState::Executing)
        timing.executing = cycle;
    else if (state == Enums::StageState::Finished)
        timing.finished = cycle;
    else if (state == Enums::StageState::Written)
        timing.written = cycle;
}
