#ifndef ENUMS_H
#define ENUMS_H

enum class Opcode { LOAD, STORE, BEQ, CALL, RET, ADD, SUB, AND, MUL };
enum class RSClass { Empty, Load, Store, Branch, CallRet, AddSub, And, Mul };
//enum class InputMode { ManualOneByOne, ManualBlock, File };
enum class StageState { Waiting, Issued, Executing, Finished, Written };
enum class InputMode { MANUAL_ONE_BY_ONE, MANUAL_BLOCK, FILE };


#endif // ENUMS_H