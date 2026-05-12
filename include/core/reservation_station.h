#ifndef RESERVATION_STATION_H
#define RESERVATION_STATION_H

// Required headers
#include "core/enums.h"
#include "core/memory.h"
#include "core/register_file.h"
#include <cstdint>
#include <string>

// Class representing a reservation station entry
class ReservationStation {
  // Properties
  Memory *memory = nullptr;
  int id;
  Enums::RSClass type;
  bool busy;
  Enums::Opcode op;
  int instruction_id;

  // Operands and dependencies
  bool has_vj;
  bool has_vk;
  uint16_t vj;
  uint16_t vk;
  int qj;
  int qk;

  // Address / special field
  uint16_t A;
  bool branch;

  // Execution state
  bool started;
  bool finished;
  int remaining_cycles;

  // Result
  uint16_t result;
  int result_address;

  public:
  // Constructor
  ReservationStation(int id, Enums::RSClass type, Memory &memory);

  // Methods
  void clear();
  void allocate(Enums::Opcode op, int instruction_id, uint16_t vj, uint16_t vk, int qj, int qk, uint16_t A);
  bool is_free() const;
  bool operands_ready() const;
  void start_execution();
  void execute();
  void write_result();  
  int get_id() const;
  void set_vj(uint16_t v);
  void set_vk(uint16_t v);
  void set_qj(int tag);
  void set_qk(int tag);
  void setA(uint16_t value);

};

#endif // RESERVATION_STATION_H