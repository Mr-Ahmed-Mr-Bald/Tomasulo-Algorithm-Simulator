#include "../../include/core/memory.h"

uint16_t Memory::load(int address) const{
    if(address < data.capacity() && address >= 0) //should we check against size, capacity, or mem_size
        return data[address];
    return -1;
}

void Memory::store(int address, uint16_t value){
    if(address < data.capacity() && address >= 0)
        data[address] = value;
}

