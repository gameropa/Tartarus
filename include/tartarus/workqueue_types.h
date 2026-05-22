#ifndef TARTARUS_WORKQUEUE_TYPES_H
#define TARTARUS_WORKQUEUE_TYPES_H

#include <tartarus/int_types.h>
#include <tartarus/queue_types.h>

struct WorkQueue {
	u32 element_size;
	struct LFQueue lfqueue;
};

#endif /* TARTARUS_WORKQUEUE_TYPES_H */
