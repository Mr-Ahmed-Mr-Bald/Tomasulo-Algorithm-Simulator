#include "simulation/write_stage.h"

#include <algorithm>

namespace {
/// @brief Returns whether the opcode produces a register result that must be broadcast
bool writes_to_register(Enums::Opcode opcode) {
    return opcode == Enums::Opcode::LOAD ||
           opcode == Enums::Opcode::ADD ||
           opcode == Enums::Opcode::SUB ||
           opcode == Enums::Opcode::AND ||
           opcode == Enums::Opcode::MUL ||
           opcode == Enums::Opcode::CALL;
}

/// @brief Broadcasts a produced value to waiting stations and matching register-file entries
void broadcast_result(SimulatorState& state, int producer_station_id, int destination_register, uint16_t value) {
    for (ReservationStation* station : state.stations.get_all_stations()) {
        if (station->is_free())
            continue;

        if (station->get_qj() == producer_station_id) {
            station->set_qj(Config::FREE_RESERVATION_STATION);
            station->set_vj(value);
        }

        if (station->get_qk() == producer_station_id) {
            station->set_qk(Config::FREE_RESERVATION_STATION);
            station->set_vk(value);
        }
    }

    if (destination_register >= 0) {
        state.registers.write(destination_register, value);
    }

    for (int reg = 0; reg < Config::NUM_REGS; ++reg) {
        if (state.registers.get_producer(reg) == producer_station_id) {
            state.registers.clear_producer(reg);
        }
    }
}
}

/// @brief Performs a single write-back action, including branch recovery when needed
void WriteBackStage::run(
    SimulatorState& state,
    Stat& stats,
    const std::vector<Instruction*>& issue_queue,
    std::vector<Instruction*>& write_back_queue,
    std::vector<Instruction*>& finished_instructions,
    ControlState& control
) {
    (void)issue_queue;

    if (write_back_queue.empty())
        return;

    auto next_to_write = std::min_element(
        write_back_queue.begin(),
        write_back_queue.end(),
        [](const Instruction* lhs, const Instruction* rhs) {
            return lhs->get_dynamic_id() < rhs->get_dynamic_id();
        }
    );

    Instruction* instruction = *next_to_write;
    ReservationStation* station = state.stations.get_by_instruction_id(instruction->get_dynamic_id());

    if (station == nullptr) {
        write_back_queue.erase(next_to_write);
        return;
    }

    if (writes_to_register(station->get_op())) {
        broadcast_result(state, station->get_id(), instruction->get_dest(), station->get_result());
    }

    if (station->get_op() == Enums::Opcode::BEQ && station->branch_taken()) {
        stats.record_misprediction();
        control.flush_requested = true;
        control.flush_after_id = instruction->get_dynamic_id();
        control.pc_changed = true;
        control.next_pc = station->get_result_address();
        state.jump_to_address(control.next_pc);
    }

    if (station->get_op() == Enums::Opcode::RET) {
        control.pc_changed = true;
        control.next_pc = station->get_result_address();
        state.jump_to_address(control.next_pc);
        control.pending_jump_id = Config::UNSET_INSTRUCTION_ID;
    }

    instruction->set_stage_state(Enums::StageState::Written);
    instruction->set_timing(Enums::StageState::Written, state.cycle);
    finished_instructions.push_back(instruction);
    stats.record_instruction_completed();

    station->clear();
    write_back_queue.erase(next_to_write);
}
