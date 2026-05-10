#ifndef CONFIG_H
#define CONFIG_H

constexpr int WORD_BITS = 16;
constexpr int NUM_REGS = 8;
constexpr int MEM_SIZE = 65536; // 128 KB of memory - word addressable

// Default sizes for reservation stations and execution cycles for each class of instructions
// Load, Store, Branch, Call/Ret, Add/Sub, And, Mul
int reservation_station_size[] = { 2, 2, 2, 1, 4, 2, 1 };
int execution_cycles[] = { 8, 8, 1, 1, 2, 1, 8 };

int get_reservation_station_size(int);
int get_execution_cycles(int);

#endif // CONFIG_H