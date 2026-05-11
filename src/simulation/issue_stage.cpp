#include "../../include/simulation/issue_stage.h"

RSClass IssueStage::instruction_class(Instruction inst){
    Opcode op = inst.get_opcode();
    if(inst.get_opcode() == Opcode::ADD || inst.get_opcode() == Opcode::SUB)
        return RSClass::AddSub;
    else if(inst.get_opcode() == Opcode::AND)
        return RSClass::And;
    else if(inst.get_opcode() == Opcode::BEQ)
        return RSClass::Branch;
    else if(inst.get_opcode() == Opcode::CALL || inst.get_opcode() == Opcode::RET)
        return RSClass::CallRet;
    else if(inst.get_opcode() == Opcode::LOAD)
        return RSClass::Load;
    else if(inst.get_opcode() == Opcode::MUL)
        return RSClass::Mul;
    else if(inst.get_opcode() == Opcode::STORE)
        return RSClass::Store;
    else   
        return RSClass::Empty;
}

int IssueStage::get_latency(RSClass class_type){
    int index = 0;
    for (int i = 1; i < 8; i++){
        if(class_type == RSClass(i)){
            index = i-1;
            break;
        }
    }
    return execution_cycles[index];
}


void IssueStage::run(){
    Instruction inst = state.program.get(state.pc_index); //current instruction
    RSClass inst_class = instruction_class(inst);
    ReservationStation rs = *state.stations.find_free(inst_class);
    int latency = get_latency(inst_class);

    if(rs.station_type() == RSClass::Empty); //if empty then we have to halt and return

    rs.allocate(inst.get_opcode(), instructionId, latency);
    
    int rd = inst.get_dest();
    int rs1 = inst.get_src1();
    int rs2 = inst.get_src2();

    //check if source is available or if we are gonna have to wait for a producer
    if(state.registers.get_producer(rs1) != 0)
        rs.set_qj(rs1);
    else
        rs.set_vj(state.registers.read(rs1));

    if(state.registers.get_producer(rs2) != 0)
        rs.set_qk(rs2);
    else
        rs.set_vk(state.registers.read(rs2));

    //mark the destination register to be produced
    state.registers.set_producer(rd, rs.get_id()); 
    
    //once you've allocated to reservation station, you're already done with issue stage
}