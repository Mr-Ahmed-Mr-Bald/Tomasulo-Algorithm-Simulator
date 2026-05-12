#ifndef WRITE_STAGE_H
#define WRITE_STAGE_H

#include "core/simulator_state.h"
#include "core/stats.h"
#include "simulation/stage_context.h"
#include <vector>

namespace WriteBackStage {
  void run(
      SimulatorState& state,
      Stat& stats,
      const std::vector<Instruction*>& issue_queue,
      std::vector<Instruction*>& write_back_queue,
      std::vector<Instruction*>& finished_instructions,
      ControlState& control
  );
}

#endif // WRITE_STAGE_H
