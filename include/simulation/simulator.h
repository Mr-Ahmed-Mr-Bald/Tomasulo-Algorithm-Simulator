#ifndef SIMULATOR_H
#define SIMULATOR_H

// Required headers
#include "../core/config.h"
#include "../core/program.h"
#include "../core/instruction.h"
#include "../core/station_manager.h"
#include "../core/simulator_state.h"
#include "../core/stats.h"

// Class representing the main controller of the Tomasulo execution
class Simulator {
  // Properties
  SimulatorState state;
  Stat stats;
  std::vector<Instruction*> completed_instructions;

  public:
  // Constructor
  Simulator(const Program& program, const std::vector<std::pair<int,uint16_t>>& initial_data);

  // Methods
  void run();
  bool step_cycle();
  bool issue_stage();
  bool execute_stage();
  bool write_back_stage();
  bool can_halt() const;
  const SimulatorState& get_state() const;
  const Stat& get_stats() const;
};

#endif // SIMULATOR_H