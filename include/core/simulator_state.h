#ifndef SIMULATOR_STATE_H
#define SIMULATOR_STATE_H

/*
SimulatorState

This is the full machine state in one place.

Properties
Config config
Program program
RegisterFile registers
Memory memory
StationManager stations
std::unique_ptr<BranchPredictor> predictor
int cycle = 0
int pcIndex = 0 // next instruction to issue
bool halted = false
Methods
void reset()
bool finished() const
Instruction* currentInstruction()
void advancePC()
void jumpToAddress(int address)
*/

// Required headers
#include "config.h"
#include "program.h"
#include "register_file.h"
#include "memory.h"
#include "reservation_station.h"
#include "station_manager.h"

// Class representing the full state of the simulator
class SimulatorState {
  // Properties
  Program program;
  RegisterFile registers;
  Memory memory;
  StationManager stations;
  int cycle = 0;
  int pc_index = 0; // next instruction to issue
  bool halted = false;

  public:
  // Constructor
  SimulatorState(const Program& program);

  // Methods
  void reset();
  bool finished() const;
  Instruction* current_instruction();
  void advance_pc();
  void jump_to_address(int address);
};

#endif // SIMULATOR_STATE_H