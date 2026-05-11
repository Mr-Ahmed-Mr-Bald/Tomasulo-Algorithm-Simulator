#include "../../include/core/config.h"

//get number of reservation stations for functioning unit at given address 
int get_reservation_station_num(int addr){
    if(addr < 7 && addr >= 0)
        return reservation_station_num[addr];
    return -1;
}

//get the number of execution cycles for functioning unit at given address
int get_execution_cycles(int address){
    if(address < 7 && address >= 0)
        return execution_cycles[address];
    return -1;
}