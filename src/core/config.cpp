#include "core/config.h"

namespace Config {
    
    // Get number of reservation stations for functioning unit at given address 
    int get_reservation_station_num(int address) {
        if (address < 0 || address >= NUM_FUNCTIONAL_UNITS)
            throw std::out_of_range("Address out of range");
        return reservation_station_num[address];
    }
    
    // Get the number of execution cycles for functioning unit at given address
    int get_execution_cycles(int address){
        if (address < 0 || address >= NUM_FUNCTIONAL_UNITS)
            throw std::out_of_range("Address out of range");
        return execution_cycles[address];
    }

}