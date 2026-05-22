#ifndef TARTARUS_BUILD_BUG_H
#define TARTARUS_BUILD_BUG_H

#include <tartarus/compiler.h>

#define BUILD_BUG_ON_MSG(cond, msg) compiletime_assert(!(cond), msg)

#define static_assert(expr, ...) __static_assert(expr, ##__VA_ARGS__, #expr)
#define __static_assert(expr, msg, ...) _Static_assert(expr, msg)

#endif /* TARTARUS_BUILD_BUG_H */
