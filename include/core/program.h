#ifndef PROGRAM_H
#define PROGRAM_H

// Required headers
#include "instruction.h"
#include <vector>
#include <unordered_map>
#include <stdexcept>

// Class representing a program consisting of a sequence of instructions and labels
class Program {
  // Properties
  int start_address;
  std::vector<Instruction> instructions;

  public:
  // Constructor
  Program(int start_address) : start_address(start_address) {}

  // Methods
  void add_instruction(const Instruction& inst);
  Instruction get(int index) const;
  int size() const;
  int Program::get_start_address() const;
  bool empty() const;

};

#endif // PROGRAM_H