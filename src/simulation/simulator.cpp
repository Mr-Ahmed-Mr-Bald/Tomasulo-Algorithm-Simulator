#include "simulation/simulator.h"

Simulator::Simulator(const Program& program, const std::vector<std::pair<int,uint16_t>>& initial_data) 
: state(program) {
    
    // Preload memory with initial data
    for (const auto& [address, value] : initial_data) {
        state.memory.preload(address, value);
    }

}

// Run the simulation until completion
void Simulator::run() {
}

// Get the current state of the simulator
const SimulatorState& Simulator::get_state() const {
    return state;
}

// Get the current statistics of the simulation
const Stat& Simulator::get_stats() const {
    return stats;
}
