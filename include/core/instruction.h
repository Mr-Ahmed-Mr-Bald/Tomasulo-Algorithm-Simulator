#ifndef INSTRUCTION_H
#define INSTRUCTION_H

// Required headers
#include "enums.h"
#include "string"

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
  Instruction(int, Opcode, int, int, int, const std::string&);

  // Gettters
  int getIndex() const;
  std::string getRawInstruction() const;
  Opcode getOpcode() const;
  int getDest() const;
  int getSrc1() const;
  int getSrc2() const;
  StageState getStageState() const;
  InstructionTiming getTiming() const;
  
  // Setters
  void setStageState(StageState);
  void setTiming(InstructionTiming);
};

#endif // INSTRUCTION_H