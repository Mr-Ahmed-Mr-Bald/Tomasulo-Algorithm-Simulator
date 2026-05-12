#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

// Required headers
#include "core/config.h"
#include "core/instruction.h"
#include "core/memory.h"
#include "core/register_file.h"
#include "core/simulator_state.h"
#include "core/stats.h"
#include <vector>

// Class responsible for generating reports of the simulation
class ReportGenerator {
  public:
  void print_instruction_table(const std::vector<Instruction*>& instructions) const;
  void print_stats(const Stat& stats) const;
  void print_register_file(const RegisterFile& rf) const;
  void print_memory(const Memory& memory) const;
  void print_final_report(
      const std::vector<Instruction*>& instructions,
      const SimulatorState& state,
      const Stat& stats
  ) const;
};

#endif // REPORT_GENERATOR_H
