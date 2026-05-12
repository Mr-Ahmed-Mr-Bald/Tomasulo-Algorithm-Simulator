#include "core/app.h"
#include <iostream>
#include <stdexcept>
#include <cstdint>

//Construction
App::App() {}


/// @brief Gathers the program by reading assembly instructions and start address from the user then parsing into a program object
/// @return the parsed program object
Program App::gather_program() {
    // 1. Choose input mode
    Enums::InputMode mode = input_manager.choose_input_mode();

    // 2. Read assembly instructions
    std::vector<std::string> lines;

    if (mode == Enums::InputMode::MANUAL) {
        lines = input_manager.read_manual();
    }
    else if (mode == Enums::InputMode::FILE) {
        lines = input_manager.read_from_user_file();
    }
    else {
        throw std::runtime_error("Unsupported input mode");
    }

    // 3. Read start address
    int start_address = input_manager.read_start_address();

    // 4. Parse program
    Program program = parser.parse(lines, start_address);

    return program;
}


/// @brief Gathers initial data for memory initialization from the user
/// @return a vector of pairs representing the initial memory data
std::vector<std::pair<int, uint16_t>> App::gather_data() {
    return input_manager.read_initial_memory_data();
}

/// @brief Runs the simulator from optional hardware configuration to final reporting
void App::run() {
    configure_functional_units();
    Program program = gather_program();
    std::vector<std::pair<int, uint16_t>> initial_data = gather_data();

    Simulator simulator(program, initial_data);
    simulator.run();
    display_results(simulator);
}

/// @brief Displays the final results of the simulation including instruction table, stats, and final report
void App::display_results(const Simulator& simulator) {
    report_generator.print_final_report(
        simulator.get_instruction_trace(),
        simulator.get_state(),
        simulator.get_stats()
    );
}

/// @brief Reads and applies optional hardware configuration overrides entered by the user
void App::configure_functional_units() {
    std::vector<int> user_units = input_manager.read_functional_unit_sizes();
    std::vector<int> user_cycles = input_manager.read_functional_unit_cycles();

    // Empty vectors => keep defaults
    if (user_units.empty() && user_cycles.empty()) {
        std::cout << "Using default hardware configuration.\n";
        return;
    }

    // Override reservation station counts
    if (!user_units.empty()) {
        for (int i = 0; i < Config::NUM_FUNCTIONAL_UNITS; ++i) {
            Config::reservation_station_num[i] = user_units[i];
        }
    }

    // Override execution latencies
    if (!user_cycles.empty()) {
        for (int i = 0; i < Config::NUM_FUNCTIONAL_UNITS; ++i) {
            Config::execution_cycles[i] = user_cycles[i];
        }
    }

    std::cout << "Custom hardware configuration applied.\n";
}
