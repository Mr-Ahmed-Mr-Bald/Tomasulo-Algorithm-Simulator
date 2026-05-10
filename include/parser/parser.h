#ifndef PARSER_H
#define PARSER_H

// Required headers
#include "../core/config.h"
#include "../core/program.h"
#include "../core/instruction.h"

// Class responsible for parsing assembly text into a Program
class Parser {
  // Properties
  public:
  // Constructor
  Parser();

  // Methods
  Program parse(const std::vector<std::string>& lines, int start_address);
  Instruction parse_line(const std::string& line, int address);
  bool is_valid_register(const std::string& token) const;
  bool is_valid_opcode(const std::string& token) const;
};

#endif // PARSER_H