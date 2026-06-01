#ifndef TARTARUS_QUEUE_H
#define TARTARUS_QUEUE_H

#include <tartarus/compiler.h>
#include <tartarus/int_types.h>
#include <tartarus/queue_types.h>

/**
 * @brief Standard enqueue function, pushes value at the tail.
 *
 * @param queue 	Queue to push the value at the tail
 * @param val		Value pointer to an array (address to a byte)
 * @param size 		Size of the value-array
 * @return bool 	False if maximum size is reached
 */
static inline bool push_tail_queue(struct Queue *queue, const void *val,
				   usize size)
{
	if (unlikely(curr_queue_size(queue) + size > queue->max_size))
		return false;

	const u8 *src = val;

	for (usize i = 0; i < size; ++i)
		queue->buff[(queue->tail + i) & queue->mask] = src[i];

	queue->tail += size;
	return true;
}

/**
 * @brief Pushes the value at the head of the queue, important for deque.
 *
 * @param queue 	Queue to push the value at the head
 * @param val 		Value pointer to an array (address to a byte)
 * @param size  	Size of the value-array
 * @return bool 	False if maximum size is reached
 */
static inline bool push_head_queue(struct Queue *queue, const void *val,
				   usize size)
{
	if (unlikely(curr_queue_size(queue) + size > queue->max_size))
		return false;

	const u8 *src = val;

	usize start = queue->head - size;

	for (usize i = 0; i < size; ++i)
		queue->buff[(start + i) & queue->mask] = src[i];

	queue->head -= size;
	return true;
}

/**
 * @brief Standard dequeue function, pops bytes of a specific size at the head
 * and writes it to the out-array.
 *
 * @param queue		Queue to pop from the head
 * @param out 		Pointer to the out-array (address to a byte)
 * @param size		Size of bytes to pop
 * @return bool		False if pop leads to a smaller size than 0
 */
static inline bool pop_head_queue(struct Queue *queue, void *out, usize size)
{
	if (unlikely(curr_queue_size(queue) < size))
		return false;

	u8 *dest = out;

	for (usize i = 0; i < size; ++i)
		dest[i] = queue->buff[(queue->head + i) & queue->mask];

	queue->head += size;
	return true;
}

/**
 * @brief Pops a specific number of bytes from the tail and writes them to out.
 *
 * @param queue 	Queue to pop from the tail
 * @param out 		Pointer to the out-array (address to a byte)
 * @param size 		Size of bytes to pop
 * @return bool 	False if pop leads to a smaller size than 0
 */
static inline bool pop_tail_queue(struct Queue *queue, void *out, usize size)
{
	if (unlikely(curr_queue_size(queue) < size))
		return false;

	u8 *dest = out;

	usize start = queue->tail - size;

	for (usize i = 0; i < size; ++i)
		dest[i] = queue->buff[(start + i) & queue->mask];

	queue->tail -= size;
	return true;
}

#define pusht_auto(q, val)                                 \
	({                                                 \
		auto __tmp = (val);                        \
		push_tail_queue(q, &__tmp, sizeof(__tmp)); \
	})

#define pushh_auto(q, val)                                 \
	({                                                 \
		auto __tmp = (val);                        \
		push_head_queue(q, &__tmp, sizeof(__tmp)); \
	})

#define poph_auto(q, out)                                 \
	({                                                \
		auto __out = (out);                       \
		pop_head_queue(q, __out, sizeof(*__out)); \
	})

#define popt_auto(q, out)                                 \
	({                                                \
		auto __out = (out);                       \
		pop_tail_queue(q, __out, sizeof(*__out)); \
	})

static inline bool push_tail_lfqueue_spmc(struct LFQueue *queue,
					  const void *val, usize size)
{
	if (unlikely(curr_lfqueue_size(queue) + size > queue->max_size))
		return false;

	const u8 *src = val;

	for (usize i = 0; i < size; ++i)
		queue->buff[(queue->tail + i) & queue->mask] = src[i];

	__atomic_store_n(&queue->tail, queue->tail + size, __ATOMIC_RELEASE);
	return true;
}

#endif /* TARTARUS_QUEUE_H */
