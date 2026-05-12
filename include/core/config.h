#ifndef CONFIG_H
#define CONFIG_H

#include <stdexcept>

namespace Config {
  
  constexpr int WORD_BITS = 16;
  constexpr int NUM_REGS = 8;
  constexpr int NUM_FUNCTIONAL_UNITS = 7;
  constexpr int MEM_SIZE = 65536; // 128 KB of memory - word addressable

  constexpr int FREE_RESERVATION_STATION = -1;
  constexpr int UNSET_INSTRUCTION_ID = -1;
  constexpr int CDB_FREE = -1; // Common data bus
  
  // Default number of reservation stations and execution cycles for each class of instructions
  // Load, Store, Branch, Call/Ret, Add/Sub, And, Mul
  int reservation_station_num[] = { 2, 2, 2, 1, 4, 2, 1 };
  int execution_cycles[] = { 8, 8, 1, 1, 2, 1, 8 };
  
  int get_reservation_station_num(int);
  int get_execution_cycles(int);

}

#endif // CONFIG_H