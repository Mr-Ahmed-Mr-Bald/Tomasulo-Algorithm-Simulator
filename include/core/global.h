#ifndef GLOBAL_H
#define GLOBAL_H

// Required headers
#include <cstdint>
#include "core/config.h"

namespace Global {
  extern int CDB = Config::CDB_FREE; // Common Data Bus tag of the instruction currently writing back
  extern std::uint16_t CDB_value = 0; // Value being written back on the CDB
  extern int halted = false; // Whether the simulator has halted
  extern bool branch_mispredicted = false; // Whether a branch was mispredicted in the current cycle
  extern bool unconditional_jump = false; // Whether an unconditional jump was taken in the current cycle
  extern bool return_from_call = false; // Whether a return from call was taken in the current cycle
}

#endif // GLOBAL_H