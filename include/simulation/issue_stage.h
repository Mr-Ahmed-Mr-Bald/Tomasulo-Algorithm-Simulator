#ifndef ISSUE_STAGE_H
#define ISSUE_STAGE_H

#include "core/simulator_state.h"
#include "core/stats.h"
#include "simulation/stage_context.h"
#include <memory>
#include <vector>

namespace IssueStage {
  bool run(
      SimulatorState& state,
      Stat& stats,
      std::vector<std::unique_ptr<Instruction>>& instruction_pool,
      std::vector<Instruction*>& issue_queue,
      ControlState& control
  );
}

#endif // ISSUE_STAGE_H
