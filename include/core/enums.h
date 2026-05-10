#ifndef ENUMS_H
#define ENUMS_H

enum class InstructionType { LOAD, STORE, BEQ, CALL, RET, ADD, SUB, AND, MUL };
enum class RSClass { Load, Store, Branch, CallRet, AddSub, And, Mul };
enum class InputMode { ManualOneByOne, ManualBlock, File };
enum class StageState { Waiting, Issued, Executing, Finished, Written };

#endif // ENUMS_H