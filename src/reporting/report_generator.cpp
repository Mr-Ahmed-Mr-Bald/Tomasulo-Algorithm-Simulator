#include "reporting/report_generator.h"

#include <iomanip>
#include <iostream>

/// @brief Prints the dynamic instruction timing table collected during simulation
void ReportGenerator::print_instruction_table(const std::vector<Instruction*>& instructions) const {
    std::cout << "\nInstruction Timing Table\n";
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(28) << "Instruction"
              << std::setw(10) << "Issue"
              << std::setw(10) << "Start"
              << std::setw(10) << "Finish"
              << std::setw(10) << "Write"
              << "\n";

    for (const Instruction* instruction : instructions) {
        const InstructionTiming timing = instruction->get_timing();
        std::cout << std::left
                  << std::setw(6)  << instruction->get_dynamic_id()
                  << std::setw(28) << instruction->get_raw_instruction()
                  << std::setw(10) << timing.issued
                  << std::setw(10) << timing.executing
                  << std::setw(10) << timing.finished
                  << std::setw(10) << timing.written
                  << "\n";
    }
}

/// @brief Prints the aggregate performance metrics required by the project description
void ReportGenerator::print_stats(const Stat& stats) const {
    std::cout << "\nPerformance Metrics\n";
    std::cout << "Instructions completed: " << stats.get_completed_instructions() << "\n";
    std::cout << "Conditional branches:   " << stats.get_branch_count() << "\n";
    std::cout << "Cycles spanned:         " << stats.get_cycles_spanned() << "\n";
    std::cout << "IPC:                    " << std::fixed << std::setprecision(2) << stats.ipc() << "\n";
    std::cout << "Misprediction %:        " << std::fixed << std::setprecision(2)
              << stats.misprediction_percent() << "\n";
}

/// @brief Prints the final architectural register file contents
void ReportGenerator::print_register_file(const RegisterFile& rf) const {
    std::cout << "\nRegister File\n";
    for (int reg = 0; reg < Config::NUM_REGS; ++reg) {
        std::cout << "R" << reg << " = " << rf.read(reg) << "\n";
    }
}

/// @brief Prints all non-zero memory locations after simulation completes
void ReportGenerator::print_memory(const Memory& memory) const {
    std::cout << "\nModified / Non-zero Memory\n";

    bool has_non_zero_values = false;
    for (int address = 0; address < Config::MEM_SIZE; ++address) {
        uint16_t value = memory.load(address);
        if (value != 0) {
            has_non_zero_values = true;
            std::cout << "[" << address << "] = " << value << "\n";
        }
    }

    if (!has_non_zero_values) {
        std::cout << "No non-zero memory values.\n";
    }
}

/// @brief Prints the full final report shown to the user after the simulation ends
void ReportGenerator::print_final_report(
    const std::vector<Instruction*>& instructions,
    const SimulatorState& state,
    const Stat& stats
) const {
    print_instruction_table(instructions);
    print_stats(stats);
    print_register_file(state.registers);
    print_memory(state.memory);
}
