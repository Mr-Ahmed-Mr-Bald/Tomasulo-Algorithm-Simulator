#include "parser/input_parser.h"
#include <algorithm>
#include <cctype>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

InputParser::InputParser() {}

namespace {
std::string normalize_line(std::string line) {
    for (char& ch : line) {
        if (ch == ',' || ch == '(' || ch == ')') {
            ch = ' ';
        }
    }
    return line;
}

std::string uppercase(std::string token) {
    std::transform(token.begin(), token.end(), token.begin(), [](unsigned char ch) {
        return static_cast<char>(std::toupper(ch));
    });
    return token;
}
}

/// @brief Parses a vector of assembly instruction lines into a Program object, starting from the specified start address
/// @param lines the assembly instruction lines to parse 
/// @param start_address the line number of the first instruction to execute, used as the starting index for instructions in the Program
/// @return the parsed Program object
Program InputParser::parse(const std::vector<std::string>& lines, int start_address) {
    Program program(start_address);

    int pc = start_address;

    for (const auto& line : lines) {
        if (line.find_first_not_of(" \t\r\n") == std::string::npos)
            continue;

        Instruction inst = parse_line(line, pc);
        program.add_instruction(inst);
        pc++;
    }

    return program;
}

/// @brief parses a single line of assembly instruction into an Instruction object, extracting the opcode and operands based on the instruction format
/// @param line the string line of assembly instruction to parse
/// @param address the line number of the instruction, used as the index for the Instruction object
/// @return the parsed Instruction object
Instruction InputParser::parse_line(const std::string& line, int address) {
    std::stringstream ss(normalize_line(line));
    std::string opcode_token;
    ss >> opcode_token;
    opcode_token = uppercase(opcode_token);

    if (!is_valid_opcode(opcode_token)) {
        throw std::runtime_error("Invalid opcode: " + opcode_token);
    }

    static const std::unordered_map<std::string, Enums::Opcode> opcode_table = {
        {"LOAD",  Enums::Opcode::LOAD},
        {"STORE", Enums::Opcode::STORE},
        {"BEQ",   Enums::Opcode::BEQ},
        {"CALL",  Enums::Opcode::CALL},
        {"RET",   Enums::Opcode::RET},
        {"ADD",   Enums::Opcode::ADD},
        {"SUB",   Enums::Opcode::SUB},
        {"AND",   Enums::Opcode::AND},
        {"MUL",   Enums::Opcode::MUL}
    };

    Enums::Opcode opcode = opcode_table.at(opcode_token);

    // Default unused operands
    int rd = -1, rs1 = -1, rs2 = -1;

    //instruction decoding based on opcode
    if (opcode == Enums::Opcode::RET) {
        return Instruction(address, opcode, -1, 1, -1, line);
    }

    if (opcode == Enums::Opcode::CALL) {
        int target;

        if (!(ss >> target)) {
            throw std::runtime_error("CALL requires target address");
        }

        return Instruction(address, opcode,
                           1,      // CALL always writes the return address to R1
                           -1,
                           target, // call target
                           line);
    }


    if (opcode == Enums::Opcode::ADD ||
        opcode == Enums::Opcode::SUB ||
        opcode == Enums::Opcode::AND ||
        opcode == Enums::Opcode::MUL) {

        std::string rd_token, rs1_token, rs2_token;

        if (!(ss >> rd_token >> rs1_token >> rs2_token))
            throw std::runtime_error("Invalid arithmetic instruction format");

        if (!is_valid_register(rd_token) ||
            !is_valid_register(rs1_token) ||
            !is_valid_register(rs2_token))
            throw std::runtime_error("Invalid register in arithmetic instruction");

        rd  = std::stoi(rd_token.substr(1));
        rs1 = std::stoi(rs1_token.substr(1));
        rs2 = std::stoi(rs2_token.substr(1));

        return Instruction(address, opcode, rd, rs1, rs2, line);
    }

    if (opcode == Enums::Opcode::LOAD ||
        opcode == Enums::Opcode::STORE) {

        std::string rd_token;
        int offset;
        std::string rs_token;

        if (!(ss >> rd_token >> offset >> rs_token))
            throw std::runtime_error("Invalid memory instruction format");

        if (!is_valid_register(rd_token) || !is_valid_register(rs_token))
            throw std::runtime_error("Invalid register in memory instruction");

        rd  = std::stoi(rd_token.substr(1));
        rs1 = std::stoi(rs_token.substr(1));
        rs2 = offset;  // using src2 to store offset

        return Instruction(address, opcode, rd, rs1, rs2, line);
    }

    if (opcode == Enums::Opcode::BEQ) {
        std::string r1, r2;
        int offset;

        if (!(ss >> r1 >> r2 >> offset))
            throw std::runtime_error("Invalid BEQ format");

        if (!is_valid_register(r1) || !is_valid_register(r2))
            throw std::runtime_error("Invalid register in BEQ");

        rs1 = std::stoi(r1.substr(1));
        rs2 = std::stoi(r2.substr(1));

        return Instruction(address, opcode, offset, rs1, rs2, line);
    }

    throw std::runtime_error("Unhandled instruction: " + line);
}

/// @brief checks if a given token is a valid register in the format "r0" to "r7"
/// @param token the string token to validate as a register
/// @return true if the token is a valid register, false otherwise
bool InputParser::is_valid_register(const std::string& token) const {
    if (token.size() < 2 || (token[0] != 'r' && token[0] != 'R'))
        return false;

    try {
        int reg = std::stoi(token.substr(1));
        return reg >= 0 && reg < Config::NUM_REGS;
    } catch (...) {
        return false;
    }
}

/// @brief checks if a given token is a valid opcode from the supported instruction set
/// @param token the string token to validate as an opcode
/// @return true if the token is a valid opcode, false otherwise
bool InputParser::is_valid_opcode(const std::string& token) const {
    static const std::unordered_set<std::string> valid_ops = {
        "LOAD", "STORE", "BEQ", "CALL", "RET",
        "ADD", "SUB", "AND", "MUL"
    };
    return valid_ops.count(token) > 0;
}
