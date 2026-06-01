#ifndef TARTARUS_LIN_ALGEBRA_QUATERNION_H
#define TARTARUS_LIN_ALGEBRA_QUATERNION_H

#include <tartarus/lin_algebra/vec3.h>

struct Quaternion {
	union {
		struct {
			float scal;
			struct Vec3 vec;
		};
		struct {
			float w, i, j, k;
		};
		float arr[4];
	};
} __attribute__((aligned(16)));

static inline struct Quaternion add_quat(struct Quaternion *a,
					 struct Quaternion *b)
{
	struct Quaternion res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a->arr[i] + b->arr[i];
	return res;
}

static inline struct Quaternion sub_quat(struct Quaternion *a,
					 struct Quaternion *b)
{
	struct Quaternion res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a->arr[i] - b->arr[i];
	return res;
}

static inline float dot_product_quat(struct Quaternion *a, struct Quaternion *b)
{
	float res = 0.0f;
	for (int i = 0; i < 4; ++i)
		res += a->arr[i] * b->arr[i];
	return res;
}

static inline struct Quaternion mult_quat(struct Quaternion *a,
					  struct Quaternion *b)
{
	struct Quaternion res;
	res.scal = a->scal * b->scal - dot_product_v3(&a->vec, &b->vec);

	struct Vec3 cross = cross_product_v3(&a->vec, &b->vec);

	for (int i = 0; i < 3; ++i)
		res.vec.vec[i] = (a->scal * b->vec.vec[i]) +
				 (b->scal + a->vec.vec[i]) + cross.vec[i];
	return res;
}

#endif /* TARTARUS_LIN_ALGEBRA_QUATERNION_H */
