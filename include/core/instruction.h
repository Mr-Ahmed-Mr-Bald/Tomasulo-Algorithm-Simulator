#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// Required headers
#include "enums.h"
#include <string>

class InstructionTiming {
  public:
  int issued;
  int executing;
  int finished;
  int written;
  InstructionTiming() : issued(-1), executing(-1), finished(-1), written(-1) {}
};

// Class representing an instruction in the pipeline
class Instruction {
  // Properties
  int index;
  std::string raw_instruction;
  Opcode opcode;
  int dest;
  int src1;
  int src2;
  StageState stage_state;
  InstructionTiming timing;

  public:

  // Constructor
  Instruction(int index, Opcode opcode, int dest, int src1, int src2, const std::string& raw_instruction);

  // Getters
  int get_index() const;
  std::string get_raw_instruction() const;
  Opcode get_opcode() const;
  int get_dest() const;
  int get_src1() const;
  int get_src2() const;
  StageState get_stage_state() const;
  InstructionTiming get_timing() const;

  // Setters
  void set_stage_state(StageState state);
  void set_timing(StageState state, int cycle);
};

#endif // INSTRUCTION_H