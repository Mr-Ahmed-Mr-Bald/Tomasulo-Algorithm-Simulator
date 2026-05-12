#include "simulation/exec_stage.h"

#include <algorithm>

namespace {
/// @brief Returns whether the opcode belongs to the memory pipeline
bool is_memory_operation(Enums::Opcode opcode) {
    return opcode == Enums::Opcode::LOAD || opcode == Enums::Opcode::STORE;
}

/// @brief Checks whether an older store still blocks a younger load
bool has_older_busy_store(const SimulatorState& state, int instruction_id) {
    for (const ReservationStation* station : state.stations.get_stations_of_type(Enums::RSClass::Store)) {
        if (!station->is_free() && station->get_instruction_id() < instruction_id) {
            return true;
        }
    }
    return false;
}

/// @brief Checks whether an older memory operation still blocks a younger store
bool has_older_busy_memory_operation(const SimulatorState& state, int instruction_id) {
    for (const ReservationStation* station : state.stations.get_all_stations()) {
        if (station->is_free())
            continue;

        if (station->get_instruction_id() >= instruction_id)
            continue;

        if (is_memory_operation(station->get_op()))
            return true;
    }

    return false;
}
}

/// @brief Advances execution for all eligible reservation stations in the current cycle
void ExecStage::run(
    SimulatorState& state,
    Stat& stats,
    const std::vector<Instruction*>& issue_queue,
    std::vector<Instruction*>& write_back_queue,
    std::vector<Instruction*>& finished_instructions,
    int execution_barrier_id
) {
    for (ReservationStation* station : state.stations.get_all_stations()) {
        if (station->is_free())
            continue;

        const int instruction_id = station->get_instruction_id();
        if (execution_barrier_id != Config::UNSET_INSTRUCTION_ID && instruction_id > execution_barrier_id)
            continue;

        Instruction* instruction = issue_queue[instruction_id];

        if (!station->has_started()) {
            if (!station->operands_ready())
                continue;

            if (station->get_op() == Enums::Opcode::LOAD && has_older_busy_store(state, instruction_id))
                continue;

            if (station->get_op() == Enums::Opcode::STORE &&
                has_older_busy_memory_operation(state, instruction_id))
                continue;

            station->start_execution();
            instruction->set_stage_state(Enums::StageState::Executing);
            instruction->set_timing(Enums::StageState::Executing, state.cycle);
            continue;
        }

        if (station->has_finished())
            continue;

        station->decrement_cycle();
        if (station->get_remaining_cycles() > 0)
            continue;

        station->execute();
        instruction->set_stage_state(Enums::StageState::Finished);
        instruction->set_timing(Enums::StageState::Finished, state.cycle);

        if (station->get_op() == Enums::Opcode::STORE) {
            instruction->set_stage_state(Enums::StageState::Written);
            instruction->set_timing(Enums::StageState::Written, state.cycle);
            finished_instructions.push_back(instruction);
            stats.record_instruction_completed();
            station->clear();
            continue;
        }

        if (std::find(write_back_queue.begin(), write_back_queue.end(), instruction) == write_back_queue.end()) {
            write_back_queue.push_back(instruction);
        }
    }
}
