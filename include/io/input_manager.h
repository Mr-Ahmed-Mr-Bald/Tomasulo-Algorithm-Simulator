#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

// Required headers
#include "../core/enums.h"
#include <string>
#include <vector>

class InputManager {
  public:
  // Constructor
  InputManager();

  // Methods
  InputMode choose_input_mode();
  std::vector<std::string> read_manual_one_by_one();
  std::vector<std::string> read_manual_block();
  std::vector<std::string> read_from_file(const std::string& path);
  int read_start_address();
  std::vector<std::pair<int, uint16_t>> read_initial_memory_data();
};

#endif // INPUT_MANAGER_H