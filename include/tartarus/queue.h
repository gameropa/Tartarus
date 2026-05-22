#ifndef TARTARUS_QUEUE_H
#define TARTARUS_QUEUE_H

#include <tartarus/compiler.h>
#include <tartarus/int_types.h>
#include <tartarus/queue_types.h>

static inline bool enqueue(struct Queue *queue, const void *val, usize size)
{
	if (unlikely(curr_queue_size(queue) + size > queue->max_size))
		return false;

	const u8 *src = val;

	for (usize i = 0; i < size; ++i)
		queue->buff[(queue->tail + i) & queue->mask] = src[i];

	queue->tail += size;
	return true;
}

static inline bool dequeue(struct Queue *queue, void *out, usize size)
{
	if (unlikely(curr_queue_size(queue) < size))
		return false;

	u8 *dest = out;

	for (usize i = 0; i < size; ++i)
		dest[i] = queue->buff[(queue->head + i) & queue->mask];

	queue->head += size;
	return true;
}

static inline bool pop_queue(struct Queue *queue, void *out, usize size)
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

#define enqueue_auto(q, val)                       \
	({                                         \
		auto __tmp = (val);                \
		enqueue(q, &__tmp, sizeof(__tmp)); \
	})

#define dequeue_auto(q, out)                       \
	({                                         \
		auto __out = (out);                \
		dequeue(q, __out, sizeof(*__out)); \
	})

#define pop_queue_auto(q, out)                       \
	({                                           \
		auto __out = (out);                  \
		pop_queue(q, __out, sizeof(*__out)); \
	})

static inline bool lfenqueue_spmc(struct LFQueue *queue, const void *val,
				  usize size)
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
