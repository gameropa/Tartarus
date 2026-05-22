#ifndef TARTARUS_INT_TYPES_H
#define TARTARUS_INT_TYPES_H

typedef int i8 __attribute__((mode(QI)));
typedef int i16 __attribute__((mode(HI)));
typedef int i32 __attribute__((mode(SI)));
typedef int i64 __attribute__((mode(DI)));
typedef int i128 __attribute__((mode(TI)));

typedef unsigned int u8 __attribute__((mode(QI)));
typedef unsigned int u16 __attribute__((mode(HI)));
typedef unsigned int u32 __attribute__((mode(SI)));
typedef unsigned int u64 __attribute__((mode(DI)));
typedef unsigned int u128 __attribute__((mode(TI)));

typedef __SIZE_TYPE__ usize;
typedef __UINTPTR_TYPE__ uptr;
typedef __INTPTR_TYPE__ iptr;
typedef __PTRDIFF_TYPE__ idiff;

#define __int8_t_defined
#define __int16_t_defined
#define __int32_t_defined
#define __int64_t_defined

#if (!defined(__STDC_VERSION__) || __STDC_VERSION__ < 202311L) && \
	!defined(__cplusplus)
#ifndef nullptr
#define nullptr ((void *)0)
typedef void *nullptr_t;
#endif

#ifndef __bool_true_false_are_defined
#define bool _Bool
#define true 1
#define false 0
#define __bool_true_false_are_defined
#endif
#endif

#define NULL ((void *)0)

#endif /* TARTARUS_INT_TYPES_H */
