#ifndef RESERVATION_STATION_H
#define RESERVATION_STATION_H

/*
This is one reservation station entry.

Properties
int id
RSClass type
bool busy = false
Opcode op = Opcode::ADD
int instructionId = -1

Operands and dependencies:

bool hasVj = false
bool hasVk = false
uint16_t Vj = 0
uint16_t Vk = 0
int Qj = -1
int Qk = -1

Address / special field:

int A = 0 // offset / effective address / branch target helper

Execution state:

bool started = false
bool finished = false
int remainingCycles = 0
int totalLatency = 0

Result:

uint16_t result = 0
int resultAddress = -1 // useful for STORE/LOAD if needed
Methods
void clear()
void allocate(Opcode op, int instrId, int latency)
bool isFree() const
bool operandsReady() const
bool canStartExecution() const
void startExecution()
void tick()
bool done() const
void setVj(uint16_t v)
void setVk(uint16_t v)
void setQj(int tag)
void setQk(int tag)
std::string dump() const
*/
// Required headers
#include "enums.h"
#include <cstdint>
#include <string>

// Class representing a reservation station entry
class ReservationStation {
  // Properties
  int id;
  RSClass type;
  bool busy;
  Opcode op;
  int instructionId;

  // Operands and dependencies
  bool hasVj;
  bool hasVk;
  uint16_t Vj;
  uint16_t Vk;
  int Qj;
  int Qk;

  // Address / special field
  int A;
  bool branch;

  // Execution state
  bool started;
  bool finished;
  int remainingCycles;
  int totalLatency;

  // Result
  uint16_t result;
  int resultAddress;

  public:
  // Constructor
  ReservationStation(int id, RSClass type);

  // Methods
  void clear();
  void allocate(Opcode op, int instrId, int latency);
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