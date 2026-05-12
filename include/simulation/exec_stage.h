#ifndef EXEC_STAGE_H
#define EXEC_STAGE_H

#include "core/simulator_state.h"
#include "core/stats.h"
#include <vector>

namespace ExecStage {
  void run(
      SimulatorState& state,
      Stat& stats,
      const std::vector<Instruction*>& issue_queue,
      std::vector<Instruction*>& write_back_queue,
      std::vector<Instruction*>& finished_instructions,
      int execution_barrier_id
  );
}

#endif // EXEC_STAGE_H
