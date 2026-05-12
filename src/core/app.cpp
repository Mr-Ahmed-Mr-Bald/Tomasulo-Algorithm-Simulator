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