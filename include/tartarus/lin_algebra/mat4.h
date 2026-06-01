#ifndef TARTARUS_LIN_ALGEBRA_MAT4_H
#define TARTARUS_LIN_ALGEBRA_MAT4_H

#include <tartarus/lin_algebra/vec4.h>

struct Mat4 {
	union {
		struct {
			struct Vec4 right;
			struct Vec4 up;
			struct Vec4 forw;
			struct Vec4 pos;
		};
		struct Vec4 cols[4];
		float arr[16];
	};
};

#endif /* TARTARUS_LIN_ALGEBRA_MAT4_H */
