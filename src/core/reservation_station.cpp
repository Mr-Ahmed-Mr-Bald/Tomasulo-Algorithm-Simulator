#include "../../include/core/reservation_station.h"
#include "../../include/core/memory.h"

ReservationStation::ReservationStation(int id, RSClass type) :
    id(id), type(type){
        started = 0;
        finished = 0;
        remainingCycles = 0;
        totalLatency = 0;
    }

void ReservationStation::allocate(Opcode op, int instrId, int latency){ 
    busy = true;
    this->op = op;
    this->instructionId = instrId;
    totalLatency = latency; 
}

bool ReservationStation::is_free() const{
    return !busy;
}

bool ReservationStation::operands_ready() const{
    return Qj == 0 && Qk == 0;
}

bool ReservationStation::canStart_execution() const{
    return operands_ready();
}

void ReservationStation::set_vj(uint16_t v){
    Vj = v;
}

void ReservationStation::set_vk(uint16_t v){
    Vk = v;
}

void ReservationStation::set_qj(int tag){
    Qj = tag;
}

void ReservationStation::set_qk(int tag){
    Qk = tag;
}

void ReservationStation::setA(int value){
    A = value;
}

//enum class Opcode { LOAD, STORE, BEQ, CALL, RET, ADD, SUB, AND, MUL };
//enum class RSClass { Load, Store, Branch, CallRet, AddSub, And, Mul };
//int reservation_station_num[] = { 2, 2, 2, 1, 4, 2, 1 };
//int execution_cycles[] = { 8, 8, 1, 1, 2, 1, 8 };

//do all execution in this function, and with every clock just wait till delay is done
void ReservationStation::start_execution(){
    if(!canStart_execution()) return;

    started = true;

    if(op == Opcode::LOAD){
        result = Memory::load(Vj);
        A += Vj; //by standard, address is stored in Vj
    }

    else if(op == Opcode::STORE){
        Memory::store(A+Vj, Vk); //address, value
    }

    else if(op == Opcode::BEQ){
        if(Vj == Vk);
            //requires program counter
    }

    else if(op == Opcode::CALL){
        //requires program counter
    }

    else if(op == Opcode::RET){
        //requires program counter
    }

    else if(op == Opcode::ADD){
        result = Vj + Vk;
        //where does it store?
    }

    else if(op == Opcode::SUB){
        result = Vj - Vk;
        //where does it store?
    }
    
    else if(op == Opcode::AND){
        result = Vj & Vk;
        //where does it store?
    }

    else if(op == Opcode::MUL){
        result = Vj * Vk;
        //where does it store?
    }


}

    