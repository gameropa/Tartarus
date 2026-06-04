#ifndef TARTARUS_STACK_TYPES_H
#define TARTARUS_STACK_TYPES_H

#include <tartarus/int_types.h>

/**
 * @brief A basic stack implementation for any data type, since data is stored byte-wise.
 * The padding is important to prevent, that meta data lies in the same cache line as buffer-
 * data.
 */
struct Stack {
	usize max_size;
	u64 idx;
	u8 __pad[64] __attribute__((aligned(64)));
	u8 *buff;
} __attribute__((aligned(64)));

#endif /* TARTARUS_STACK_TYPES_H */
