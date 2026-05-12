#ifndef ISSUE_STAGE_H
#define ISSUE_STAGE_H

// Required headers
#include "../core/config.h"
#include "../core/program.h"
#include "../core/instruction.h"
#include "../core/station_manager.h"
#include "../core/simulator_state.h"
#include "../core/stats.h"
#include "simulator.h"

// Class representing the controller for issuing
class IssueStage {
  SimulatorState state;
  Stat stats;
  int instructionId = 0;

  RSClass instruction_class(Instruction inst);
  int get_latency(RSClass class_type);
  
  public:
  void run();
};

#endif // ISSUE_STAGE_H