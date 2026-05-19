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

#define enqueue_auto(q, val)                       \
	({                                         \
		auto __tmp = (val);                \
		enqueue(q, &__tmp, sizeof(__tmp)); \
	})

#define dequeue_auto(q, out) dequeue(q, out, sizeof(*(out)))

#endif /* TARTARUS_QUEUE_H */
