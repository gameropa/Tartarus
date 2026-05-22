#ifndef TARTARUS_STDDEF_H
#define TARTARUS_STDDEF_H

#define offsetof(type, member) __builtin_offsetof(type, member)

#define sizeof_field(type, member) sizeof((((type *)0)->member))

#define offsetofend(type, member) \
	(offsetof(type, member) + sizeof_field(type, member))

#endif /* TARTARUS_STDDEF_H */
