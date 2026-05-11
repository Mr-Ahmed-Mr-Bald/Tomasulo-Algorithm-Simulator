#include "../../include/simulation/simulator.h"

Simulator::Simulator(const Program& program, const std::vector<std::pair<int,uint16_t>>& initial_data){
    
    //create a new simulator state with memory, rf, stations, and program
    state = SimulatorState(program);
    
    //stats

    //load initial data into memory
    for(int i = 0; i < initial_data.size(); i++){
        state.memory.preload(initial_data[i].first, initial_data[i].second);
    }
}

void Simulator::run(){
    state.pc_index = state.program.get_start_address(); //start executing from specified address 
     
}
