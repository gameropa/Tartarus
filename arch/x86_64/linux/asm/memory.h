#ifndef TARTARUS_ASM_ARCH_X86_64_LINUX_MEMORY_H
#define TARTARUS_ASM_ARCH_X86_64_LINUX_MEMORY_H

#include <tartarus/compiler.h>
#include <tartarus/int_types.h>

#define PROT_READ 0x1
#define PROT_WRITE 0x2

#define MAP_PRIVATE 0x02
#define MAP_ANONYMOUS 0x20

#define MREMAP_MAYMOVE 1

extern void *sys_mmap(void *addr, usize length, int prot, int flags, int fd,
		      long offset);

static inline void *alloc_pages(usize size)
{
	void *ptr = sys_mmap(NULL, size, PROT_READ | PROT_WRITE,
			     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (unlikely((usize)ptr >= (usize)-4095))
		return NULL;

	return ptr;
}

extern int sys_munmap(void *addr, usize length);

static inline void free_pages(void *ptr, usize size)
{
	if (likely(ptr != NULL))
		(void)sys_munmap(ptr, size);
}

extern void *sys_mremap(void *old_addr, usize old_size, usize new_size,
			int flags, void *new_addr);

static inline void *resize_pages(void *old_ptr, usize old_size, usize new_size)
{
	void *ptr =
		sys_mremap(old_ptr, old_size, new_size, MREMAP_MAYMOVE, NULL);

	if (unlikely((usize)ptr >= (usize)-4095))
		return NULL;

	return ptr;
}

#endif /* TARTARUS_ASM_ARCH_X86_64_LINUX_MEMORY_H */
