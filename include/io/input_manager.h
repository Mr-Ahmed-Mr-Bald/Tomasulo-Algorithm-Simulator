#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

// Required headers
#include "../core/enums.h"
#include <string>
#include <vector>
#include <cstdint>

class InputManager {
  public:
  // Constructor
  InputManager();

  // Methods
  Enums::InputMode choose_input_mode();
  std::vector<std::string> read_manual();
  
  std::vector<std::string> read_from_user_file();
  std::vector<std::string> read_from_file(const std::string& path);
  std::string read_filename_from_user();
  
  int read_start_address();
  std::vector<std::pair<int, uint16_t>> read_initial_memory_data();
};

#endif // INPUT_MANAGER_H