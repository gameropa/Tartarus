#ifndef TARTARUS_QUEUE_TYPES_H
#define TARTARUS_QUEUE_TYPES_H

#include <tartarus/int_types.h>

struct Queue {
	usize max_size;
	u64 mask;
	u64 head;
	u64 tail;
	u8 __pad[64] __attribute__((aligned(64)));
	u8 *buff;
} __attribute__((aligned(64)));

struct LFQueue {
	usize max_size;
	u64 mask;
	u8 __pad0[64] __attribute__((aligned(64)));
	u64 head;
	u8 __pad1[64] __attribute__((aligned(64)));
	u64 tail;
	u8 __pad2[64] __attribute__((aligned(64)));
	u8 *buff;
} __attribute__((aligned(64)));

static inline usize curr_queue_size(struct Queue *queue)
{
	return queue->tail - queue->head;
}

static inline usize curr_lfqueue_size(struct LFQueue *lfqueue)
{
	usize t = __atomic_load_n(&lfqueue->tail, __ATOMIC_RELAXED);
	usize h = __atomic_load_n(&lfqueue->head, __ATOMIC_RELAXED);
	return t - h;
}

#endif /* TARTARUS_QUEUE_TYPES_H */
