#include "core/register_file.h"
#include "core/config.h"

// Constructor
RegisterFile::RegisterFile() {
    reset();
}

// Resets the register file to initial state
void RegisterFile::reset() {
    for (int i = 0; i < Config::NUM_REGS; ++i) {
        value[i] = 0;
        ready[i] = true;
        producer_tag[i] = Config::FREE_RESERVATION_STATION;
    }
}

// Checks if address is within range
bool RegisterFile::is_valid_address(int address) const {
    return (address >= 0 && address < Config::NUM_REGS); 
}

// Reads the value at the specified register
uint16_t RegisterFile::read(int address) const {
    if(is_valid_address(address))
        return value[address];
    throw std::out_of_range("Invalid register address");
}

// Writes to the specified register
void RegisterFile::write(int address, uint16_t val){
    if(is_valid_address(address))
        value[address] = val;
    else
        throw std::out_of_range("Invalid register address");
}

// Checks if the register is ready
bool RegisterFile::is_ready(int address) const {
    if(is_valid_address(address))
        return ready[address];
    throw std::out_of_range("Invalid register address");
}



// Sets the producer tag
void RegisterFile::set_producer(int address, int stationId) {
    if(is_valid_address(address)) {
        producer_tag[address] = stationId;
        ready[address] = false;
    }
}

// Clears the producer tag (set to -1)
void RegisterFile::clear_producer(int reg, int station_id) {
    if(is_valid_address(reg)) {
        producer_tag[reg] = Config::FREE_RESERVATION_STATION;
        ready[reg] = true;
    }
}
