#include "core/stats.h"

// Reset all statistics to their initial state
void Stat::reset() {
    instruction_count = 0;
    completed_instructions = 0;
    branch_count = 0;
    branch_mispredictions = 0;
    cycles_spanned = 0;
}

// Record the start of an instruction, incrementing the instruction count
void Stat::record_instruction_started() {
    instruction_count++;
}

// Record the completion of an instruction, incrementing the completed instructions count
void Stat::record_instruction_completed() {
    completed_instructions++;
}

// Record the occurrence of a branch instruction, incrementing the branch count
void Stat::record_branch() {
    branch_count++;
}

// Record a branch misprediction, incrementing the branch mispredictions count
void Stat::record_misprediction() {
    branch_mispredictions++;
}

// Set the total number of spanned cycles
void Stat::set_cycles_spanned(int cycles) {
    cycles_spanned = cycles;
}

// Get the number of issued instructions
int Stat::get_instruction_count() const {
    return instruction_count;
}

// Get the number of completed instructions
int Stat::get_completed_instructions() const {
    return completed_instructions;
}

// Get the number of encountered branches
int Stat::get_branch_count() const {
    return branch_count;
}

// Get the number of branch mispredictions
int Stat::get_branch_mispredictions() const {
    return branch_mispredictions;
}

// Get the total execution time in cycles
int Stat::get_cycles_spanned() const {
    return cycles_spanned;
}

// Calculate and return the Instructions Per Cycle (IPC) as a double
double Stat::ipc() const {
    if (cycles_spanned == 0)
        return 0.0;
    return (double)(completed_instructions) / cycles_spanned;
}

// Calculate and return the branch misprediction percentage as a double
double Stat::misprediction_percent() const {
    if (branch_count == 0)
        return 0.0;
    return (double)(branch_mispredictions) / branch_count * 100;
}
