#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

// Required headers
#include "core/config.h"
#include <array>
#include <cstdint>
#include <string>
#include <stdexcept>

// Class representing the register file
class RegisterFile {
  // Properties
  std::array<uint16_t, Config::NUM_REGS> value;
  std::array<bool, Config::NUM_REGS> ready;
  std::array<int, Config::NUM_REGS> producer_tag; // index of reservation station producing this register, or 0

  // Helpers
  bool is_valid_address(int reg) const;

  public:
  // Constructor
  RegisterFile();

  // Methods
  void reset();
  uint16_t read(int address) const;
  void write(int address, uint16_t val);
  bool is_ready(int address) const;
  int get_producer(int address) const;
  void set_producer(int address, int station_id);
  void clear_producer(int address);
};

#endif // REGISTER_FILE_H
