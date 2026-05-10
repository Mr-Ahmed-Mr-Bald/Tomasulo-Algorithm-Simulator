#include "../../include/core/stats.h"

void Stat::reset(){
    instruction_count = 0;
    completed_instructions = 0;
    branch_count = 0;
    branch_mispredictions = 0;
    cycles_spanned = 0;
}

void Stat::record_instruction_started(){
    instruction_count++;
}

void Stat::record_instruction_completed(){
    completed_instructions++;
}

void Stat::record_branch(){
    branch_count++;
}

void Stat::record_misprediction(){
    branch_mispredictions++;
}

double Stat::ipc() const{
    return (double)(completed_instructions)/cycles_spanned;
}

double Stat::misprediction_percent() const{
    return (double)(branch_mispredictions)/branch_count * 100;
}