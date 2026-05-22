#ifndef TARTARUS_COMPILER_TYPES_H
#define TARTARUS_COMPILER_TYPES_H

#define ___PASTE(a, b) a##b
#define __PASTE(a, b) ___PASTE(a, b)

#define compiletime_assert(cond, msg) _Static_assert(cond, msg)

#define __same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

#define __scalar_types_to_expr_cases(type) \
	unsigned type : (unsigned type)0, signed type : (signed type)0

#define __unqual_scalar_typeof(x)                               \
	typeof(_Generic((x),                                    \
		       char: (char)0,                           \
		       __scalar_types_to_expr_cases(char),      \
		       __scalar_types_to_expr_cases(short),     \
		       __scalar_types_to_expr_cases(int),       \
		       __scalar_types_to_expr_cases(long),      \
		       __scalar_types_to_expr_cases(long long), \
		       default: (x)))

#endif /* TARTARUS_COMPILER_TYPES_H */
