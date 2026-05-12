#ifndef STAT_H
#define STAT_H

// Required headers

// Class representing the statistics of the simulation
class Stat {
  // Properties
  int instruction_count = 0;
  int completed_instructions = 0;
  int branch_count = 0;
  int branch_mispredictions = 0;
  int cycles_spanned = 0;

  public:
  // Methods
  void reset();
  void record_instruction_started();
  void record_instruction_completed();
  void record_branch();
  void record_misprediction();
  void set_cycles_spanned(int cycles);
  int get_instruction_count() const;
  int get_completed_instructions() const;
  int get_branch_count() const;
  int get_branch_mispredictions() const;
  int get_cycles_spanned() const;
  double ipc() const;
  double misprediction_percent() const;
};

#endif // STAT_H
