#ifndef MEMORY_H
#define MEMORY_H

// Required headers
#include "config.h"
#include <vector>
#include <cstdint>

// Class representing the memory of the system
class Memory {
  // Properties
  //initialize the memory directly with the fixed mem size
  static std::vector<uint16_t> data;
  
  static bool is_valid_address(int address);

  public:
  // Methods
  static uint16_t load(int address);
  static void store(int address, uint16_t value);
  static void preload(int address, uint16_t value);
};

#endif // MEMORY_H