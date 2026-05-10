#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

// Required headers
#include "config.h"
#include <array>
#include <cstdint>
#include <string>

// Class representing the register file
class RegisterFile {
  // Properties
  std::array<uint16_t, NUM_REGS> value;
  std::array<bool, NUM_REGS> ready;
  std::array<int, NUM_REGS> producerTag; // index of reservation station producing this register, or -1

  public:
  // Constructor
  RegisterFile();

  // Methods
  void reset();
  uint16_t read(int reg) const;
  void write(int reg, uint16_t val);
  bool isReady(int reg) const;
  int getProducer(int reg) const;
  void setProducer(int reg, int stationId);
  void clearProducer(int reg, int stationId);
};

#endif // REGISTER_FILE_H