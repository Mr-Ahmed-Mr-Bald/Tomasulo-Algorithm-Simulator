#ifndef SIMULATOR_H
#define SIMULATOR_H

// Required headers
#include "core/config.h"
#include "core/program.h"
#include "core/instruction.h"
#include "core/station_manager.h"
#include "core/simulator_state.h"
#include "core/stats.h"
#include <memory>

// Class representing the main controller of the Tomasulo execution
class Simulator {
  // Properties
  SimulatorState state;
  Stat stats;
  std::vector<std::unique_ptr<Instruction>> instruction_pool;
  std::vector<Instruction*> issue_queue, execute_queue, write_back_queue, finished_instructions;

  public:
  // Constructor
  Simulator(const Program& program, const std::vector<std::pair<int,uint16_t>>& initial_data);

  // Methods
  void run();
  const SimulatorState& get_state() const;
  const Stat& get_stats() const;
  const std::vector<Instruction*>& get_instruction_trace() const;
};

#endif // SIMULATOR_H
