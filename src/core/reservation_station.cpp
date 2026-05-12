// Required headers
#include "core/reservation_station.h"
#include "core/memory.h"
#include "core/global.h"

// Constructor
ReservationStation::ReservationStation(int id, Enums::RSClass type, Memory &memory) 
    : id(id), type(type), memory(&memory)
{
    clear();
}

// Clears the reservation station entry
void ReservationStation::clear() {
    busy = false;
    op = Enums::Opcode::LOAD; // default value
    instruction_id = -1;
    has_vj = false;
    has_vk = false;
    qj = Config::FREE_RESERVATION_STATION;
    qk = Config::FREE_RESERVATION_STATION;
    branch = false;
    started = false;
    finished = false;
    remaining_cycles = 0;
}

// Allocates the reservation station for a new instruction
void ReservationStation::allocate(Enums::Opcode op_, int instruction_id_, uint16_t vj_, uint16_t vk_, int qj_, int qk_, uint16_t A_) { 
    busy = true;
    op = op_;
    instruction_id = instruction_id_;
    set_vj(vj_);
    set_vk(vk_);
    set_qj(qj_);
    set_qk(qk_);
    setA(A_);
}

// Returns whether the reservation station is free
bool ReservationStation::is_free() const {
    return !busy;
}

// Returns whether the operands are ready
bool ReservationStation::operands_ready() const {
    return qj == Config::FREE_RESERVATION_STATION && qk == Config::FREE_RESERVATION_STATION;
}

// Returns the unique ID of the reservation station
int ReservationStation::get_id() const {
    return id;
}

// Sets the value of operand j
void ReservationStation::set_vj(uint16_t v) {
    vj = v;
}

// Sets the value of operand k
void ReservationStation::set_vk(uint16_t v) {
    vk = v;
}

// Sets the tag of the reservation station producing operand j
void ReservationStation::set_qj(int tag) {
    qj = tag;
}

// Sets the tag of the reservation station producing operand k
void ReservationStation::set_qk(int tag) {
    qk = tag;
}

// Sets the value of the address field A
void ReservationStation::setA(uint16_t value) {
    A = value;
}

// Executes the instruction in the reservation station
void ReservationStation::start_execution() {
    // Mark started as true
    started = true;
}

void ReservationStation::execute() {

    switch(op) {
        case Enums::Opcode::LOAD:
            A += vj;
            result = memory->load(A);
            break;
        
        case Enums::Opcode::STORE:
            memory->store(A + vj, vk); // address, value
            break;
        
        case Enums::Opcode::BEQ:
            if (vj == vk) {
                Global::branch_mispredicted = true;
            }
            break;
        
        case Enums::Opcode::CALL:
            Global::unconditional_jump = true;
            result = A;
            break;
        
        case Enums::Opcode::RET:
            Global::return_from_call = true;
            break;

        case Enums::Opcode::ADD:
            result = vj + vk;
            break;

        case Enums::Opcode::SUB:
            result = vj - vk;
            break;
        
        case Enums::Opcode::AND:
            result = vj & vk;
            break;

        case Enums::Opcode::MUL:
            result = vj * vk;
            break;
    }
}

void ReservationStation::write_result() {
    if (Global::CDB == Config::CDB_FREE) {
        Global::CDB = instruction_id;
        Global::CDB_value = result;
        finished = true;
    }
}