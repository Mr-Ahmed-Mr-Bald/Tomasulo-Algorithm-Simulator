#ifndef MEMORY_H
#define MEMORY_H

// Required headers
#include "config.h"
#include <vector>
#include <cstdint>

// Class representing the memory of the system
class Memory {
  // Properties
  std::vector<uint16_t> data;

  public:
  // Constructor
  Memory(int size = MEM_SIZE);

  // Methods
  uint16_t load(int address) const;
  void store(int address, uint16_t value);
  void preload(int address, uint16_t value);
  bool is_valid_address(int address) const;
};

#endif // MEMORY_H