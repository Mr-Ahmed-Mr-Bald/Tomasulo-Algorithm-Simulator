#ifndef ENUMS_H
#define ENUMS_H

namespace Enums {
  enum class Opcode { LOAD, STORE, BEQ, CALL, RET, ADD, SUB, AND, MUL };
  enum class RSClass { Load, Store, Branch, CallRet, AddSub, And, Mul };
  enum class StageState { Waiting, Issued, Executing, Finished, Written };
  enum class InputMode { MANUAL, FILE };
}


#endif // ENUMS_H
