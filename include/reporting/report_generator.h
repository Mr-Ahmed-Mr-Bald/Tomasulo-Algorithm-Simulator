#ifndef REPORT_GENERATOR_H
#define REPORT_GENERATOR_H

// Required headers
#include "../core/config.h"
#include "../core/program.h"
#include "../core/simulator_state.h"

// Class responsible for generating reports of the simulation
class ReportGenerator {
  // Properties
  public:
  // Constructor
  ReportGenerator();

  // Methods
  void print_instruction_table(const Program& program) const;
  void print_stats(const SimulatorState& state) const;
  void print_final_report(const Program& program, const SimulatorState& state) const;
  void print_station_state(const StationManager& stations) const;
  void print_register_file(const RegisterFile& rf) const;
};

#endif // REPORT_GENERATOR_H