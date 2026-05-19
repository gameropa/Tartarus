#ifndef TARTARUS_COMPILER_TYPES_H
#define TARTARUS_COMPILER_TYPES_H

#define ___PASTE(a, b) a##b
#define __PASTE(a, b) ___PASTE(a, b)

#define compiletime_assert(cond, msg) _Static_assert(cond, msg)

#endif /* TARTARUS_COMPILER_TYPES_H */
