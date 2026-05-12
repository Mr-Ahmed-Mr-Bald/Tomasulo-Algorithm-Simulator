#include "core/reservation_station.h"
#include "core/memory.h"

// Constructor
ReservationStation::ReservationStation(Enums::RSClass type) : type(type) {
    started = 0;
    finished = 0;
    remaining_cycles = 0;
}

void ReservationStation::allocate(Enums::Opcode op, int instruction_id, int latency){ 
    busy = true;
    this->op = op;
    this->instruction_id = instruction_id;
}

RSClass ReservationStation::station_type() const{
    return type;
}

bool ReservationStation::is_free() const{
    return !busy;
}

bool ReservationStation::operands_ready() const{
    return qj == 0 && qk == 0;
}

bool ReservationStation::canStart_execution() const{
    return operands_ready();
}

void ReservationStation::set_vj(uint16_t v){
    vj = v;
}

void ReservationStation::set_vk(uint16_t v){
    vk = v;
}

void ReservationStation::set_qj(int tag){
    qj = tag;
}

void ReservationStation::set_qk(int tag){
    qk = tag;
}

void ReservationStation::setA(int value){
    A = value;
}

int ReservationStation::get_id() const{
    return id;
}

//enum class Opcode { LOAD, STORE, BEQ, CALL, RET, ADD, SUB, AND, MUL };
//enum class RSClass { Load, Store, Branch, CallRet, AddSub, And, Mul };
//int reservation_station_num[] = { 2, 2, 2, 1, 4, 2, 1 };
//int execution_cycles[] = { 8, 8, 1, 1, 2, 1, 8 };

//do all execution in this function, and with every clock just wait till delay is done
void ReservationStation::start_execution(){
    if(!canStart_execution()) return;

    started = true;

    if(op == Enums::Opcode::LOAD){
        result = Memory::load(vj);
        A += vj; //by standard, address is stored in vj
    }

    else if(op == Opcode::STORE){
        Memory::store(A+vj, vk); //address, value
    }

    else if(op == Opcode::BEQ){
        if(vj == vk);
            //requires program counter
    }

    else if(op == Opcode::CALL){
        //requires program counter
    }

    else if(op == Opcode::RET){
        //requires program counter
    }

    else if(op == Opcode::ADD){
        result = vj + vk;
        //where does it store?
    }

    else if(op == Opcode::SUB){
        result = vj - vk;
        //where does it store?
    }
    
    else if(op == Opcode::AND){
        result = vj & vk;
        //where does it store?
    }

    else if(op == Opcode::MUL){
        result = vj * vk;
        //where does it store?
    }


}

    