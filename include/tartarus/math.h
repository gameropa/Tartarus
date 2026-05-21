#ifndef TARTARUS_MATH_H
#define TARTARUS_MATH_H

#include <tartarus/compiler.h>
#include <tartarus/int_types.h>
#include <asm/math.h>

#define __round_mask(x, y) ((__typeof__(x))((y) - 1))

#define round_up(x, y) ((((x) - 1) | __round_mask(x, y)) + 1)

#define round_down(x, y) ((x) & ~__round_mask(x, y))

#define roundup(x, y)                            \
	({                                       \
		typeof(y) __y = (y);             \
		(((x) + (__y - 1)) / __y) * __y; \
	})

#define rounddown(x, y)              \
	({                           \
		typeof(x) __x = (x); \
		__x - (__x % (y));   \
	})

#define abs(x)                                                                        \
	__abs_choose_expr(                                                            \
		x, long long,                                                         \
		__abs_choose_expr(                                                    \
			x, long,                                                      \
			__abs_choose_expr(                                            \
				x, int,                                               \
				__abs_choose_expr(                                    \
					x, short,                                     \
					__abs_choose_expr(                            \
						x, char,                              \
						__builtin_choose_expr(                \
							__builtin_types_compatible_p( \
								typeof(x),            \
								char),                \
							(char)({                      \
								signed char __x =     \
									(x);          \
								__x < 0 ?             \
									-__x :        \
									__x;          \
							}),                           \
							((void)0)))))))

#define __abs_choose_expr(x, type, other)                               \
	__builtin_choose_expr(                                          \
		__builtin_types_compatible_p(typeof(x), signed type) || \
			__builtin_types_compatible_p(typeof(x),         \
						     unsigned type),    \
		({                                                      \
			signed type __x = (x);                          \
			__x < 0 ? -__x : __x;                           \
		}),                                                     \
		other)

#define abs_diff(a, b)                                 \
	({                                             \
		typeof(a) __a = (a);                   \
		typeof(b) __b = (b);                   \
		(void)(&__a == &__b);                  \
		__a > __b ? (__a - __b) : (__b - __a); \
	})

static inline u32 u32sqrt(u32 x)
{
	u32 res = 0;
	u32 bit = 1U << 30;

	while (bit > x)
		bit >>= 2;

	while (bit != 0) {
		if (x >= res + bit) {
			x -= res + bit;
			res = (res >> 1) + bit;
		} else {
			res >>= 1;
		}
		bit >>= 2;
	}
	return res;
}

static inline u64 u64sqrt(u64 x)
{
	if (unlikely(x <= 1))
		return x;

	u32 leading_zeros = __builtin_clzll(x);
	u64 xzero = 1ULL << ((64 - leading_zeros + 1) >> 1);

	u64 xone = (xzero + x / xzero) >> 1;
	while (xone < xzero) {
		xzero = xone;
		xone = (xzero + x / xzero) >> 1;
	}

	return xzero;
}

static inline float fsqrt(float x)
{
	return x * finv_sqrt(x);
}

static inline float finv_sqrt_quake(float x)
{
	float xhalf = 0.5f * x;

	u32 i = *(u32 *)&x;
	i = 0x5f3759df - (i >> 1);
	x = *(float *)&i;

	return x * (1.5f - xhalf * x * x);
}

static inline float fsqrt_quake(float x)
{
	return x * finv_sqrt_quake(x);
}

static inline u32 u32_log2(u32 x)
{
	return (x > 0) ? 31U - __builtin_clz(x) : 0;
}

static inline u64 u64_log2(u64 x)
{
	return (x > 0) ? 63U - __builtin_clzll(x) : 0;
}

static inline u32 u32pow(u32 base, u32 exp)
{
	u32 res = 1;
	for (; exp > 0; exp >>= 1) {
		if (exp & 1)
			res *= base;
		base *= base;
	}
	return res;
}

static inline u64 u64pow(u64 base, u32 exp)
{
	u64 res = 1;
	for (; exp > 0; exp >>= 1) {
		if (exp & 1)
			res *= base;
		base *= base;
	}
	return res;
}

static inline float fpow(float x, float y)
{
	u32 i = *(u32 *)&x;
	i = (u32)(y * (float)(i - 1064866805)) + 1064866805;
	return *(float *)&i;
}

#endif /* TARTARUS_MATH_H */
