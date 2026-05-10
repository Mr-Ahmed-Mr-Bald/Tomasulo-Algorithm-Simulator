#ifndef APP_H
#define APP_H

// Required headers
#include "config.h"
#include "program.h"
#include "parser.h"
#include "../simulation/simulator.h"
#include "../reporting/report_generator.h"
#include "../io/input_manager.h"
#include "../parser/parser.h"

// Class representing the main application
class App {
  // Properties
  InputManager input_manager;
  Parser parser;
  ReportGenerator report_generator;
  public:
  // Constructor
  App();

  // Methods
  void run();
  Program gather_program();
  std::vector<std::pair<int, uint16_t>> gather_data();
  void display_results(const Program& program, const SimulatorState& state);
};

#endif // APP_H
