#ifndef TARTARUS_QUEUE_TYPES_H
#define TARTARUS_QUEUE_TYPES_H

#include <tartarus/int_types.h>

/**
 * @brief Structure for a basic, non-lock-free queue. The queue can be used as a
 * double ended queue (Deque). The padding is important to prevent that meta data and
 * buffer-data are in the same cache line. This is also important for SIMD-operations.
 *
 * @note max_size must be base 2, otherwise the queue won't work. That's because we use
 * a mask to get the actual head and tail indizes from the stored. The current indizes
 * are unsigned to make a wrap around possible, when reaching the maximum value.
 * This ensures that the true index can always be obtained.
 */
struct Queue {
	usize max_size;
	u64 mask;
	u64 head;
	u64 tail;
	u8 __pad[64] __attribute__((aligned(64)));
	u8 *buff;
} __attribute__((aligned(64)));

/**
 * @brief Structure for a lock-free queue. This queue can be used as any implementation-
 * type (spsc, spmc, mpsc, mpmc). The paddings are very important, to prevent false sharing
 * when multiple threads try to get the head or tail index.
 *
 * @note max_size must be base 2, otherwise the queue won't work. Same reason as with the
 * standard queue.
 */
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

/**
 * @brief Small helper function to get the current size of the queue.
 *
 * @param queue 	Queue to get the current size from
 * @return usize 	Current size of the queue
 */
static inline usize curr_queue_size(struct Queue *queue)
{
	return queue->tail - queue->head;
}

/**
 * @brief Small helper funtion to get the current size of the queue thread-safe.
 *
 * @param lfqueue 	Queue to get the current size from
 * @return usize 	Current size of the queue
 */
static inline usize curr_lfqueue_size(struct LFQueue *lfqueue)
{
	usize t = __atomic_load_n(&lfqueue->tail, __ATOMIC_RELAXED);
	usize h = __atomic_load_n(&lfqueue->head, __ATOMIC_RELAXED);
	return t - h;
}

#endif /* TARTARUS_QUEUE_TYPES_H */
