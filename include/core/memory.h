#ifndef MEMORY_H
#define MEMORY_H

// Required headers
#include "core/config.h"
#include <vector>
#include <cstdint>

// Class representing the memory of the system
class Memory {
  // Properties
  //initialize the memory directly with the fixed mem size
  std::vector<uint16_t> data;
  
  bool is_valid_address(int address);

  public:
  Memory() : data(Config::MEM_SIZE) {}

  // Methods
  void reset();
  uint16_t load(int address);
  void store(int address, uint16_t value);
  void preload(int address, uint16_t value);
};

#endif // MEMORY_H