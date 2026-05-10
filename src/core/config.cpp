#include "../../include/core/config.h"

int get_reservation_station_size(int addr){
    if(addr < NUM_REGS && addr > 0)
        return reservation_station_size[addr];
    return -1;
}

int get_execution_cycles(int addr){
    if(addr < NUM_REGS && addr > 0)
        return execution_cycles[addr];
    return -1;
}