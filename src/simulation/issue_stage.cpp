#include "simulation/issue_stage.h"

#include <stdexcept>

namespace {
/// @brief Maps an opcode to the reservation-station pool responsible for issuing it
Enums::RSClass get_station_type(Enums::Opcode opcode) {
    switch (opcode) {
        case Enums::Opcode::LOAD:  return Enums::RSClass::Load;
        case Enums::Opcode::STORE: return Enums::RSClass::Store;
        case Enums::Opcode::BEQ:   return Enums::RSClass::Branch;
        case Enums::Opcode::CALL:
        case Enums::Opcode::RET:   return Enums::RSClass::CallRet;
        case Enums::Opcode::ADD:
        case Enums::Opcode::SUB:   return Enums::RSClass::AddSub;
        case Enums::Opcode::AND:   return Enums::RSClass::And;
        case Enums::Opcode::MUL:   return Enums::RSClass::Mul;
    }

    throw std::runtime_error("Unsupported opcode");
}

/// @brief Converts an architectural source register into either a ready value or a producer tag
void load_register_operand(
    const RegisterFile& registers,
    int address,
    uint16_t& value,
    int& producer
) {
    if (address < 0) {
        producer = Config::FREE_RESERVATION_STATION;
        value = 0;
        return;
    }

    if (registers.is_ready(address)) {
        value = registers.read(address);
        producer = Config::FREE_RESERVATION_STATION;
    } else {
        value = 0;
        producer = registers.get_producer(address);
    }
}
}

/// @brief Issues at most one instruction into a free reservation station during the current cycle
bool IssueStage::run(
    SimulatorState& state,
    Stat& stats,
    std::vector<std::unique_ptr<Instruction>>& instruction_pool,
    std::vector<Instruction*>& issue_queue,
    ControlState& control
) {
    if (control.pending_jump_id != Config::UNSET_INSTRUCTION_ID)
        return false;

    if (!state.program.contains_address(state.pc_index))
        return false;

    const Instruction& template_instruction = state.program.get_by_address(state.pc_index);
    ReservationStation* station = state.stations.find_free(get_station_type(template_instruction.get_opcode()));

    if (station == nullptr)
        return false;

    auto dynamic_instruction = std::make_unique<Instruction>(template_instruction);
    int dynamic_id = static_cast<int>(instruction_pool.size());
    dynamic_instruction->set_dynamic_id(dynamic_id);
    dynamic_instruction->set_stage_state(Enums::StageState::Issued);
    dynamic_instruction->set_timing(Enums::StageState::Issued, state.cycle);

    uint16_t vj = 0;
    uint16_t vk = 0;
    int qj = Config::FREE_RESERVATION_STATION;
    int qk = Config::FREE_RESERVATION_STATION;
    int A = 0;

    switch (dynamic_instruction->get_opcode()) {
        case Enums::Opcode::LOAD:
            load_register_operand(state.registers, dynamic_instruction->get_src1(), vj, qj);
            A = dynamic_instruction->get_src2();
            state.registers.set_producer(dynamic_instruction->get_dest(), station->get_id());
            break;

        case Enums::Opcode::STORE:
            load_register_operand(state.registers, dynamic_instruction->get_src1(), vj, qj);
            load_register_operand(state.registers, dynamic_instruction->get_dest(), vk, qk);
            A = dynamic_instruction->get_src2();
            break;

        case Enums::Opcode::BEQ:
            load_register_operand(state.registers, dynamic_instruction->get_src1(), vj, qj);
            load_register_operand(state.registers, dynamic_instruction->get_src2(), vk, qk);
            A = dynamic_instruction->get_index() + 1 + dynamic_instruction->get_dest();
            stats.record_branch();
            if (control.pending_branch_id == Config::UNSET_INSTRUCTION_ID)
                control.pending_branch_id = dynamic_id;
            break;

        case Enums::Opcode::CALL:
            vj = static_cast<uint16_t>(dynamic_instruction->get_index() + 1);
            A = dynamic_instruction->get_src2();
            state.registers.set_producer(dynamic_instruction->get_dest(), station->get_id());
            break;

        case Enums::Opcode::RET:
            load_register_operand(state.registers, dynamic_instruction->get_src1(), vj, qj);
            control.pending_jump_id = dynamic_id;
            break;

        case Enums::Opcode::ADD:
        case Enums::Opcode::SUB:
        case Enums::Opcode::AND:
        case Enums::Opcode::MUL:
            load_register_operand(state.registers, dynamic_instruction->get_src1(), vj, qj);
            load_register_operand(state.registers, dynamic_instruction->get_src2(), vk, qk);
            state.registers.set_producer(dynamic_instruction->get_dest(), station->get_id());
            break;
    }

    station->allocate(dynamic_instruction->get_opcode(), dynamic_id, vj, vk, qj, qk, A);

    instruction_pool.push_back(std::move(dynamic_instruction));
    issue_queue.push_back(instruction_pool.back().get());
    stats.record_instruction_started();

    if (issue_queue.back()->get_opcode() == Enums::Opcode::CALL) {
        state.jump_to_address(issue_queue.back()->get_src2());
    } else {
        state.advance_pc();
    }

    return true;
}
