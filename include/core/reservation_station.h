#ifndef RESERVATION_STATION_H
#define RESERVATION_STATION_H
// Required headers
#include "core/enums.h"
#include <cstdint>
#include <string>

// Class representing a reservation station entry
class ReservationStation {
  // Properties
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
  int A;
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
  ReservationStation(Enums::RSClass type);

  // Methods
  void clear();
  void allocate(Enums::Opcode op, int instrId, int latency);
  bool is_free() const;
  bool operands_ready() const;
  bool canStart_execution() const;
  void start_execution();
  void tick();
  bool done() const;
  void set_vj(uint16_t v);
  void set_vk(uint16_t v);
  void set_qj(int tag);
  void set_qk(int tag);
  void setA(int value);

};

#endif // RESERVATION_STATION_H