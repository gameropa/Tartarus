#ifndef TARTARUS_LIN_ALGEBRA_MAT3_H
#define TARTARUS_LIN_ALGEBRA_MAT3_H

#include <tartarus/lin_algebra/vec3.h>

struct Mat3 {
	union {
		struct {
			struct Vec3 right;
			struct Vec3 up;
			struct Vec3 forw;
		};
		struct Vec3 cols[3];
		float arr[9];
	};
};

#endif /* TARTARUS_LIN_ALGEBRA_MAT3_H */
