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

// Calculate and return the Instructions Per Cycle (IPC) as a double
double Stat::ipc() const {
    return (double)(completed_instructions) / cycles_spanned;
}

// Calculate and return the branch misprediction percentage as a double
double Stat::misprediction_percent() const {
    return (double)(branch_mispredictions) / branch_count * 100;
}