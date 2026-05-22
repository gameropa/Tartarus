#ifndef TARTARUS_ASM_ARCH_X86_64_COMMON_ATOMIC_H
#define TARTARUS_ASM_ARCH_X86_64_COMMON_ATOMIC_H

#include <asm/cpu.h>
#include <tartarus/int_types.h>

static inline void spin_lock(u32 *lock)
{
	while (__atomic_exchange_n(lock, 1, __ATOMIC_ACQUIRE)) {
		cpu_pause();
	}
}

static inline void spin_unlock(u32 *lock)
{
	__atomic_store_n(lock, 0, __ATOMIC_RELEASE);
}

#endif /* TARTARUS_ASM_ARCH_X86_64_COMMON_ATOMIC_H */
