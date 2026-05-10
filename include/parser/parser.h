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
  void first_pass_collect_labels(const std::vector<std::string>& lines, std::unordered_map<std::string, int>& label_addresses);
  void second_pass_resolve_labels(Program& program, const std::unordered_map<std::string, int>& label_addresses);
  bool is_valid_register(const std::string& token) const;
  bool is_valid_opcode(const std::string& token) const;
};

#endif // PARSER_H