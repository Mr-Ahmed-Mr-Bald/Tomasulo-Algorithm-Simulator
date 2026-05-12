#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// Required headers
#include "core/enums.h"
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
  int dynamic_id;
  std::string raw_instruction;
  Enums::Opcode opcode;
  int dest;
  int src1;
  int src2;
  Enums::StageState stage_state;
  InstructionTiming timing;

  public:

  // Constructor
  Instruction(int index, Enums::Opcode opcode, int dest, int src1, int src2, const std::string& raw_instruction);

  // Getters
  int get_index() const;
  int get_dynamic_id() const;
  std::string get_raw_instruction() const;
  Enums::Opcode get_opcode() const;
  int get_dest() const;
  int get_src1() const;
  int get_src2() const;
  Enums::StageState get_stage_state() const;
  InstructionTiming get_timing() const;

  // Setters
  void set_dynamic_id(int id);
  void set_stage_state(Enums::StageState state);
  void set_timing(Enums::StageState state, int cycle);
};

#endif // INSTRUCTION_H
