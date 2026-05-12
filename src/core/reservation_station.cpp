// Required headers
#include "core/reservation_station.h"
#include "core/config.h"

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
    vj = 0;
    vk = 0;
    qj = Config::FREE_RESERVATION_STATION;
    qk = Config::FREE_RESERVATION_STATION;
    A = 0;
    branch = false;
    started = false;
    finished = false;
    remaining_cycles = 0;
    result = 0;
    result_address = 0;
}

// Allocates the reservation station for a new instruction
void ReservationStation::allocate(Enums::Opcode op_, int instruction_id_, uint16_t vj_, uint16_t vk_, int qj_, int qk_, int A_) { 
    busy = true;
    op = op_;
    instruction_id = instruction_id_;
    set_vj(vj_);
    set_vk(vk_);
    set_qj(qj_);
    set_qk(qk_);
    setA(A_);
    started = false;
    finished = false;
    remaining_cycles = 0;
    branch = false;
    result = 0;
    result_address = 0;
}

// Returns whether the reservation station is free
bool ReservationStation::is_free() const {
    return !busy;
}

// Returns whether the reservation station is busy
bool ReservationStation::is_busy() const {
    return busy;
}

// Returns whether the operands are ready
bool ReservationStation::operands_ready() const {
    return qj == Config::FREE_RESERVATION_STATION && qk == Config::FREE_RESERVATION_STATION;
}

// Returns the unique ID of the reservation station
int ReservationStation::get_id() const {
    return id;
}

// Returns the reservation station type
Enums::RSClass ReservationStation::get_type() const {
    return type;
}

// Returns the opcode stored in the station
Enums::Opcode ReservationStation::get_op() const {
    return op;
}

// Returns the current instruction id
int ReservationStation::get_instruction_id() const {
    return instruction_id;
}

// Returns whether execution already started
bool ReservationStation::has_started() const {
    return started;
}

// Returns whether execution finished
bool ReservationStation::has_finished() const {
    return finished;
}

// Returns remaining execution cycles
int ReservationStation::get_remaining_cycles() const {
    return remaining_cycles;
}

// Returns operand j value
uint16_t ReservationStation::get_vj() const {
    return vj;
}

// Returns operand k value
uint16_t ReservationStation::get_vk() const {
    return vk;
}

// Returns operand j tag
int ReservationStation::get_qj() const {
    return qj;
}

// Returns operand k tag
int ReservationStation::get_qk() const {
    return qk;
}

// Returns address field A
int ReservationStation::getA() const {
    return A;
}

// Returns branch outcome
bool ReservationStation::branch_taken() const {
    return branch;
}

// Returns the computed result
uint16_t ReservationStation::get_result() const {
    return result;
}

// Returns the computed result address
int ReservationStation::get_result_address() const {
    return result_address;
}

// Sets the value of operand j
void ReservationStation::set_vj(uint16_t v) {
    vj = v;
    has_vj = true;
}

// Sets the value of operand k
void ReservationStation::set_vk(uint16_t v) {
    vk = v;
    has_vk = true;
}

// Sets the tag of the reservation station producing operand j
void ReservationStation::set_qj(int tag) {
    qj = tag;
    has_vj = tag == Config::FREE_RESERVATION_STATION;
}

// Sets the tag of the reservation station producing operand k
void ReservationStation::set_qk(int tag) {
    qk = tag;
    has_vk = tag == Config::FREE_RESERVATION_STATION;
}

// Sets the value of the address field A
void ReservationStation::setA(int value) {
    A = value;
}

// Sets the computed result
void ReservationStation::set_result(uint16_t value) {
    result = value;
}

// Sets the computed result address
void ReservationStation::set_result_address(int address) {
    result_address = address;
}

// Sets the control-flow outcome
void ReservationStation::set_branch_taken(bool taken) {
    branch = taken;
}

// Executes the instruction in the reservation station
void ReservationStation::start_execution() {
    started = true;
    remaining_cycles = Config::get_execution_cycles(static_cast<int>(type));
}

// Decrements the remaining execution cycles
void ReservationStation::decrement_cycle() {
    if (remaining_cycles > 0) {
        remaining_cycles--;
    }
}

void ReservationStation::execute() {
    switch(op) {
        case Enums::Opcode::LOAD:
            result_address = A + vj;
            result = memory->load(result_address);
            break;
        
        case Enums::Opcode::STORE:
            result_address = A + vj;
            memory->store(result_address, vk);
            break;
        
        case Enums::Opcode::BEQ:
            branch = (vj == vk);
            result_address = A;
            break;
        
        case Enums::Opcode::CALL:
            branch = true;
            result = vj;
            result_address = A;
            break;
        
        case Enums::Opcode::RET:
            branch = true;
            result_address = vj;
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

    finished = true;
}

void ReservationStation::mark_finished() {
    finished = true;
}

void ReservationStation::write_result() {
    finished = true;
}
