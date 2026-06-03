#ifndef TARTARUS_STACK_H
#define TARTARUS_STACK_H

#include <tartarus/compiler.h>
#include <tartarus/int_types.h>
#include <tartarus/stack_types.h>

static inline bool push_stack(struct Stack *stk, const void *val, usize size)
{
	if (unlikely(stk->idx + size > stk->max_size))
		return false;

	__builtin_memcpy(&stk->buff[stk->idx], val, size);

	stk->idx += size;
	return true;
}

static inline bool pop_stack(struct Stack *stk, void *out, usize size)
{
	if (unlikely(stk->idx < size))
		return false;

	stk->idx -= size;
	if (likely(out))
		__builtin_memcpy(out, &stk->buff[stk->idx], size);

	return true;
}

#endif /* TARTARUS_STACK_H */
