#ifndef APP_H
#define APP_H

// Required headers
#include "config.h"
#include "program.h"
#include "parser/input_parser.h"
#include "simulation/simulator.h"
#include "reporting/report_generator.h"
#include "io/input_manager.h"


// Class representing the main application
class App { 
  // Properties
  InputManager input_manager;
  InputParser parser;
  ReportGenerator report_generator;
  public:
  // Constructor
  App();

  // Methods
  void run();
  Program gather_program();
  std::vector<std::pair<int, uint16_t>> gather_data();
  void display_results(const Simulator& simulator);
  
  void configure_functional_units(); 

};

#endif // APP_H
