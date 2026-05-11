#include "../../include/core/memory.h"

std::vector<uint16_t> Memory::data(MEM_SIZE);

uint16_t Memory::load(int address){
    if(is_valid_address(address)) //should we check against size, capacity, or mem_size
        return data[address];
    return -1;
}

void Memory::store(int address, uint16_t value){
    if(is_valid_address(address))
        data[address] = value;
}

void Memory::preload(int address, uint16_t value){
    store(address, value);
}

bool Memory::is_valid_address(int address){
    return (address >= 0) && (address < MEM_SIZE);
}