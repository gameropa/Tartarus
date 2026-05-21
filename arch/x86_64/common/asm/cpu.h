#ifndef TARTARUS_ASM_ARCH_X86_64_COMMON_CPU
#define TARTARUS_ASM_ARCH_X86_64_COMMON_CPU

#include <tartarus/int_types.h>

static inline void cpu_pause(void)
{
	__asm__ volatile("pause" ::: "memory");
}

static inline void cpuid(u32 code, u32 subcode, u32 abcd[4])
{
	__asm__ volatile("cpuid"
			 : "=a"(abcd[0]), "=b"(abcd[1]), "=c"(abcd[2]),
			   "=d"(abcd[3])
			 : "a"(code), "c"(subcode));
}

#endif /* TARTARUS_ASM_ARCH_X86_64_COMMON_CPU */
