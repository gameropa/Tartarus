#ifndef TARTARUS_BUILD_BUG_H
#define TARTARUS_BUILD_BUG_H

#include <tartarus/compiler.h>

#define BUILD_BUG_ON_MSG(cond, msg) compiletime_assert(!(cond), msg)

#endif /* TARTARUS_BUILD_BUG_H */
