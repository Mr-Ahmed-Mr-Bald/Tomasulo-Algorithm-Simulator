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
  ReservationStation(int id, Enums::RSClass type, Memory &memory);

  // Methods
  void clear();
  void allocate(Enums::Opcode op, int instruction_id, uint16_t vj, uint16_t vk, int qj, int qk, int A);
  bool is_free() const;
  bool is_busy() const;
  bool operands_ready() const;
  void start_execution();
  void decrement_cycle();
  void execute();
  void write_result();  
  int get_id() const;
  Enums::RSClass get_type() const;
  Enums::Opcode get_op() const;
  int get_instruction_id() const;
  bool has_started() const;
  bool has_finished() const;
  int get_remaining_cycles() const;
  uint16_t get_vj() const;
  uint16_t get_vk() const;
  int get_qj() const;
  int get_qk() const;
  int getA() const;
  bool branch_taken() const;
  uint16_t get_result() const;
  int get_result_address() const;
  void set_vj(uint16_t v);
  void set_vk(uint16_t v);
  void set_qj(int tag);
  void set_qk(int tag);
  void setA(int value);
  void set_result(uint16_t value);
  void set_result_address(int address);
  void set_branch_taken(bool taken);
  void mark_finished();

};

#endif // RESERVATION_STATION_H
