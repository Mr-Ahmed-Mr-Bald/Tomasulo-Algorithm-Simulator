#include "simulation/simulator.h"
#include "simulation/exec_stage.h"
#include "simulation/issue_stage.h"
#include "simulation/stage_context.h"
#include "simulation/write_stage.h"

#include <algorithm>

namespace {
/// @brief Returns whether the opcode eventually writes a result to the register file
bool writes_to_register(Enums::Opcode opcode) {
    return opcode == Enums::Opcode::LOAD ||
           opcode == Enums::Opcode::ADD ||
           opcode == Enums::Opcode::SUB ||
           opcode == Enums::Opcode::AND ||
           opcode == Enums::Opcode::MUL ||
           opcode == Enums::Opcode::CALL;
}

/// @brief Returns whether any reservation station is still occupied
bool has_active_stations(SimulatorState& state) {
    for (ReservationStation* station : state.stations.get_all_stations()) {
        if (!station->is_free())
            return true;
    }
    return false;
}

/// @brief Finds the oldest in-flight branch that still blocks younger execution
int first_pending_branch_id(SimulatorState& state) {
    int earliest_branch = Config::UNSET_INSTRUCTION_ID;
    for (ReservationStation* station : state.stations.get_stations_of_type(Enums::RSClass::Branch)) {
        if (station->is_free())
            continue;

        if (earliest_branch == Config::UNSET_INSTRUCTION_ID ||
            station->get_instruction_id() < earliest_branch) {
            earliest_branch = station->get_instruction_id();
        }
    }

    return earliest_branch;
}

/// @brief Clears any register producer entries associated with a flushed reservation station
void clear_register_producers_for_station(RegisterFile& registers, int station_id) {
    for (int reg = 0; reg < Config::NUM_REGS; ++reg) {
        if (registers.get_producer(reg) == station_id) {
            registers.clear_producer(reg);
        }
    }
}

/// @brief Rebuilds the register status table after a control-flow flush
void rebuild_register_status(SimulatorState& state, const std::vector<Instruction*>& issue_queue) {
    for (int reg = 1; reg < Config::NUM_REGS; ++reg) {
        state.registers.clear_producer(reg);
    }

    std::vector<ReservationStation*> active_stations = state.stations.get_all_stations();
    std::sort(
        active_stations.begin(),
        active_stations.end(),
        [](const ReservationStation* lhs, const ReservationStation* rhs) {
            return lhs->get_instruction_id() < rhs->get_instruction_id();
        }
    );

    for (ReservationStation* station : active_stations) {
        if (station->is_free())
            continue;

        const Instruction* instruction = issue_queue[station->get_instruction_id()];
        if (writes_to_register(station->get_op())) {
            state.registers.set_producer(instruction->get_dest(), station->get_id());
        }
    }
}

/// @brief Flushes all younger instructions after a taken branch and restores bookkeeping
void flush_younger_instructions(
    SimulatorState& state,
    const std::vector<Instruction*>& issue_queue,
    std::vector<Instruction*>& write_back_queue,
    int flush_after_id
) {
    for (ReservationStation* station : state.stations.get_all_stations()) {
        if (station->is_free())
            continue;

        if (station->get_instruction_id() > flush_after_id) {
            clear_register_producers_for_station(state.registers, station->get_id());
            station->clear();
        }
    }

    write_back_queue.erase(
        std::remove_if(
            write_back_queue.begin(),
            write_back_queue.end(),
            [flush_after_id](const Instruction* instruction) {
                return instruction->get_dynamic_id() > flush_after_id;
            }
        ),
        write_back_queue.end()
    );

    rebuild_register_status(state, issue_queue);
}
}

/// @brief Constructs the simulator and preloads the initial memory image
Simulator::Simulator(const Program& program, const std::vector<std::pair<int,uint16_t>>& initial_data) 
: state(program) {
    
    // Preload memory with initial data
    for (const auto& [address, value] : initial_data) {
        state.memory.preload(address, value);
    }

}

/// @brief Runs the Tomasulo simulation cycle-by-cycle until all work completes
void Simulator::run() {
    stats.reset();
    instruction_pool.clear();
    issue_queue.clear();
    execute_queue.clear();
    write_back_queue.clear();
    finished_instructions.clear();

    ControlState control;

    while (!state.finished() || has_active_stations(state) || !write_back_queue.empty()) {
        state.cycle++;

        control.flush_requested = false;
        control.flush_after_id = Config::UNSET_INSTRUCTION_ID;
        control.pc_changed = false;

        const int execution_barrier_id = control.pending_branch_id;

        WriteBackStage::run(state, stats, issue_queue, write_back_queue, finished_instructions, control);

        if (control.flush_requested) {
            flush_younger_instructions(state, issue_queue, write_back_queue, control.flush_after_id);
        }

        ExecStage::run(
            state,
            stats,
            issue_queue,
            write_back_queue,
            finished_instructions,
            execution_barrier_id
        );

        if (!control.pc_changed) {
            IssueStage::run(state, stats, instruction_pool, issue_queue, control);
        }

        control.pending_branch_id = first_pending_branch_id(state);
        if (control.pending_jump_id != Config::UNSET_INSTRUCTION_ID &&
            state.stations.get_by_instruction_id(control.pending_jump_id) == nullptr) {
            control.pending_jump_id = Config::UNSET_INSTRUCTION_ID;
        }
    }

    stats.set_cycles_spanned(state.cycle);
}

// Get the current state of the simulator
const SimulatorState& Simulator::get_state() const {
    return state;
}

// Get the current statistics of the simulation
const Stat& Simulator::get_stats() const {
    return stats;
}

const std::vector<Instruction*>& Simulator::get_instruction_trace() const {
    return issue_queue;
}
