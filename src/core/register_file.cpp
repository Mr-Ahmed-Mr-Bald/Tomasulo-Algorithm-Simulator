#include "../../include/core/register_file.h"

//checks if address is within range
bool RegisterFile::is_valid_address (int reg) const
{
    return (reg>=0 && reg < NUM_REGS); 
}

//reads the value at the specified register
uint16_t RegisterFile::read(int reg) const{
    if(is_valid_address(reg))
        return value[reg];
    return -1;
}

//writes to the specified register
void RegisterFile::write(int reg, uint16_t val){
    if(is_valid_address(reg))
        value[reg] = val;
}

//checks if the register is ready
bool RegisterFile::is_ready(int reg) const{
    if(is_valid_address(reg))
        return ready[reg];
    return false;
}

//returns the producer tag
int RegisterFile::get_producer(int reg) const{
    if(is_valid_address(reg))
        return producer_tag[reg];
    return -1;
}


//sets the producer tag
void RegisterFile::set_producer(int reg, int stationId) {
    if(is_valid_address(reg))
        producer_tag[reg] = stationId;
}

//clears the producer tag (set to -1)
void RegisterFile::clear_producer(int reg, int stationId) {
    if(is_valid_address(reg))
        producer_tag[reg] = -1;
}
