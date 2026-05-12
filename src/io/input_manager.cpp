#include "../../include/io/input_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

InputManager::InputManager() {}


/// @brief Chooses the input mode for reading assembly instrucitons
/// @return the input mode as an ENUM value 
Enums::InputMode InputManager::choose_input_mode() {
    int choice;

    std::cout << "Choose input mode:\n";
    std::cout << "1. Enter assembly instructions line by line or as one block\n";
    std::cout << "2. Enter file name\n";
    std::cout << "Enter choice: (enter 1 or 2)";

    std::cin >> choice;
    std::cin.ignore();  // clear newline

    switch (choice) {
        case 1: return Enums::InputMode::MANUAL;
        case 2: return Enums::InputMode::FILE;
        default:
            std::cerr << "Invalid input mode.\n";
            return choose_input_mode();
    }
}


/// @brief Reads assembly instructions one by one or as a block until the user types "done"
/// @return a vector of strings representing the assembly instructions
std::vector<std::string> InputManager::read_manual() {
    std::vector<std::string> instructions;
    std::string line;

    std::cout << "Enter RISCV assembly instructions (type 'done' to finish):\n";

    while (true) {
        std::getline(std::cin, line);
        if (line == "done") break;
        instructions.push_back(line);
    }

    return instructions;
}

/// @brief Prompts the user for a file name and reads assembly instructions from it
/// @return vector of assembly instruction lines
std::vector<std::string> InputManager::read_from_user_file() {
    std::string path = read_filename_from_user();
    return read_from_file(path);
}

/// @brief Prompts the user to enter an assembly file name (stored in /data)
/// @return relative path to the file as a string
std::string InputManager::read_filename_from_user() {
    std::string filename;
    std::cout << "Enter assembly file name (e.g. program.txt): ";
    std::getline(std::cin, filename);

    // Prepend relative data directory
    std::string path = "data/" + filename;

    return path;
}

/// @brief Reads assembly instructions from a file specified by the user
/// @param path to assembly file
/// @return a vector of strings representing the assembly instructions
std::vector<std::string> InputManager::read_from_file(const std::string& path) {
    std::vector<std::string> instructions;
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << path << "\n";
        return instructions;
    }

    while (std::getline(file, line)) {
        if (!line.empty())
            instructions.push_back(line);
    }

    file.close();
    return instructions;
}


/// @brief Reads the start address in the program as the line number of the first instruction to execute
/// @return Integer representing the start address
int InputManager::read_start_address() {
    int address;
    std::cout << "Enter start address: ";
    std::cin >> address;
    std::cin.ignore();
    return address;
}


/// @brief Prompts the user to input initial memory data in the format (address, value) until they type "done"
/// @return Returns a vector of pairs where each pair contains a memory address and its corresponding value for initialization
std::vector<std::pair<int, uint16_t>> InputManager::read_initial_memory_data() {
    std::vector<std::pair<int, uint16_t>> memory_data;
    std::string line;

    std::cout << "Enter data memory initialization (128KB or 65536 addresses) in the following formate: (address, value)\n";
    std::cout << "Type 'done' to finish:\n";

    while (true) {
        std::getline(std::cin, line);
        if (line == "done") break;

        std::stringstream ss(line);
        int address;
        uint16_t value;
        char comma;

        if (ss >> address >> comma >> value && comma == ',') {
            memory_data.emplace_back(address, value);
        } else {
            std::cerr << "Invalid format. Use: address, value\n";
        }
    }

    return memory_data;
}