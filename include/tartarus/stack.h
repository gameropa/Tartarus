#ifndef TARTARUS_STACK_H
#define TARTARUS_STACK_H

#include <tartarus/compiler.h>
#include <tartarus/int_types.h>
#include <tartarus/stack_types.h>

/**
 * @brief Pushes data to the stack of any size.
 *
 * @param stk 		The stack to push data to.
 * @param val 		The value pointer to an array.
 * @param size 		The size of the array in bytes.
 * @return bool		Returns false if a stack overflow were to occur.
 */
static inline bool push_stack(struct Stack *stk, const void *val, usize size)
{
	if (unlikely(stk->idx + size > stk->max_size))
		return false;

	__builtin_memcpy(&stk->buff[stk->idx], val, size);

	stk->idx += size;
	return true;
}

/**
 * @brief Pops data of a specific size from a stack and writes it into the
 * out-array.
 *
 * @param stk		The stack to pop data from .
 * @param out 		The out pointer to an array.
 * @param size 		The size to pop.
 * @return bool		Returns false if more data is taken than is present.
 */
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
