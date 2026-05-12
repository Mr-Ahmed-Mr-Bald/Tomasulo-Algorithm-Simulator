#include "core/app.h"
#include <iostream>

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

/// @brief Displays the final results of the simulation including instruction table, stats, and final report
void App::configure_functional_units() {
    std::vector<int> user_units =
        input_manager.read_functional_unit_sizes();

    // Empty vector => keep defaults
    if (user_units.empty()) {
        std::cout << "Using default functional unit configuration.\n";
        return;
    }

    // Override defaults
    for (int i = 0; i < Config::NUM_FUNCTIONAL_UNITS; ++i) {
        Config::reservation_station_num[i] = user_units[i];
    }

    std::cout << "Custom functional unit configuration applied.\n";
}
