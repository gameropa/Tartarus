#ifndef TARTARUS_ASM_ARCH_X86_64_COMMON_MATH
#define TARTARUS_ASM_ARCH_X86_64_COMMON_MATH

#include <tartarus/int_types.h>

static inline float finv_sqrt(float x)
{
	float res;

	__asm__("rsqrtss %1, %0" : "=x"(res) : "x"(x));

	return res * (1.5f - (x * 0.5f * res * res));
}

static inline u32 rotl32(u32 x, u8 r)
{
	__asm__("roll %b1, %0" : "+r"(x) : "c"(r));
	return x;
}

static inline u32 rotr32(u32 x, u8 r)
{
	__asm__("rorl %b1, %0" : "+r"(x) : "c"(r));
	return x;
}

static inline u64 rotl64(u64 x, u8 r)
{
	__asm__("rolq %b1, %0" : "+r"(x) : "c"(r));
	return x;
}

static inline u64 rotr64(u64 x, u8 r)
{
	__asm__("rorq %b1, %0" : "+r"(x) : "c"(r));
	return x;
}

#endif /* TARTARUS_ASM_ARCH_X86_64_COMMON_MATH */
