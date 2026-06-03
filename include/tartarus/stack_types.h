#ifndef TARTARUS_STACK_TYPES_H
#define TARTARUS_STACK_TYPES_H

#include <tartarus/int_types.h>

struct Stack {
	usize max_size;
	u64 idx;
	u8 __pad[64] __attribute__((aligned(64)));
	u8 *buff;
} __attribute__((aligned(64)));

struct LFStack {
	usize max_size;
	u8 __pad0[64] __attribute__((aligned(64)));
	u64 idx;
	u8 __pad1[64] __attribute__((aligned(64)));
	u8 *buff;
} __attribute__((aligned(64)));

#endif /* TARTARUS_STACK_TYPES_H */
