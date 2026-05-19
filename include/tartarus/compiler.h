#ifndef TARTARUS_COMPILER_H
#define TARTARUS_COMPILER_H

#include <tartarus/compiler_types.h>
#include <tartarus/int_types.h>

#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define __UNIQUE_ID(name) \
	__PASTE(__UNIQUE_ID_, __PASTE(name, __PASTE(_, __COUNTER__)))

static inline void *offset_to_ptr(const i32 *off)
{
	return (void *)((u64 *)off + *off);
}

#define is_signed_type(type) (((type)(-1) < (__force type)1))
#define is_unsigned_type(type) (!is_signed_type(type))

#define statically_true(x) (__builtin_constant_p(x) && (x))

#endif /* TARTARUS_COMPILER_H */
