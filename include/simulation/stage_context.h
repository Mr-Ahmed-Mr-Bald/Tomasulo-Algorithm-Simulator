#ifndef STAGE_CONTEXT_H
#define STAGE_CONTEXT_H

#include "core/config.h"

struct ControlState {
  int pending_branch_id = Config::UNSET_INSTRUCTION_ID;
  int pending_jump_id = Config::UNSET_INSTRUCTION_ID;
  bool flush_requested = false;
  int flush_after_id = Config::UNSET_INSTRUCTION_ID;
  bool pc_changed = false;
  int next_pc = 0;
};

#endif // STAGE_CONTEXT_H
