#include "core/memory.h"

void Memory::reset(){
    std::fill(data.begin(), data.end(), 0);
}

uint16_t Memory::load(int address){
    if (is_valid_address(address)) 
        return data[address];
    throw std::out_of_range("Invalid memory address");
}

void Memory::store(int address, uint16_t value){
    if (is_valid_address(address))
        data[address] = value;
    else
        throw std::out_of_range("Invalid memory address");
}

void Memory::preload(int address, uint16_t value){
    store(address, value);
}

bool Memory::is_valid_address(int address){
    return (address >= 0) && (address < Config::MEM_SIZE);
}