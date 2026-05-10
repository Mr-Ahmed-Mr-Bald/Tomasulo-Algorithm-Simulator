#ifndef PROGRAM_H
#define PROGRAM_H

// Required headers
#include "instruction.h"
#include <vector>
#include <unordered_map>

// Class representing a program consisting of a sequence of instructions and labels
class Program {
  // Properties
  int startAddress;
  std::vector<Instruction> instructions;

  public:
  // Constructor
  Program(int startAddress) : startAddress(startAddress) {}

  // Methods
  void addInstruction(const Instruction& inst);
  Instruction& get(int index);
  const Instruction& get(int index) const;
  int size() const;
  bool empty() const;

};

#endif // PROGRAM_H