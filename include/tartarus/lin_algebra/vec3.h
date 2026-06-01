#ifndef TARTARUS_LIN_ALGEBRA_VEC3_H
#define TARTARUS_LIN_ALGEBRA_VEC3_H

#include <tartarus/compiler.h>
#include <tartarus/math.h>

struct Quaternion;

struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float vec[3];
	};
} __attribute__((packed));

static inline struct Vec3 add_v3(const struct Vec3 *a, const struct Vec3 *b)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.vec[i] = a->vec[i] + b->vec[i];
	return res;
}

static inline struct Vec3 sub_v3(const struct Vec3 *a, const struct Vec3 *b)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.vec[i] = a->vec[i] - b->vec[i];
	return res;
}

static inline struct Vec3 comp_mult_v3(const struct Vec3 *a,
				       const struct Vec3 *b)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.vec[i] = a->vec[i] * b->vec[i];
	return res;
}

static inline struct Vec3 comp_div_v3(const struct Vec3 *a,
				      const struct Vec3 *b)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.vec[i] = a->vec[i] / b->vec[i];
	return res;
}

static inline void mult_scal_v3(struct Vec3 *x, float scalar)
{
	for (int i = 0; i < 3; ++i)
		x->vec[i] *= scalar;
}

static inline void div_scal_v3(struct Vec3 *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_v3(x, inv_scal);
}

static inline float dot_product_v3(const struct Vec3 *a, const struct Vec3 *b)
{
	float res = 0.0f;
	for (int i = 0; i < 3; ++i)
		res += a->vec[i] * b->vec[i];
	return res;
}

static inline struct Vec3 cross_product_v3(const struct Vec3 *a,
					   const struct Vec3 *b)
{
	struct Vec3 res;

	res.x = a->y * b->z - a->z * b->y;
	res.y = a->z * b->x - a->x * b->z;
	res.z = a->x * b->y - a->y * b->x;

	return res;
}

static inline float triple_product_v3(const struct Vec3 *a,
				      const struct Vec3 *b,
				      const struct Vec3 *c)
{
	struct Vec3 cross_prod = cross_product_v3(a, b);
	return dot_product_v3(&cross_prod, c);
}

static inline float sqlen_v3(const struct Vec3 *x)
{
	return dot_product_v3(x, x);
}

static inline float len_v3(const struct Vec3 *x)
{
	float sqsum = sqlen_v3(x);
	return fsqrt(sqsum);
}

static inline void norm_v3(struct Vec3 *x)
{
	float len = len_v3(x);
	if (likely(len > 0.0f))
		div_scal_v3(x, len);
}

static inline float dist_v3(const struct Vec3 *a, const struct Vec3 *b)
{
	struct Vec3 diff = sub_v3(a, b);
	return len_v3(&diff);
}

static inline float sqdist_v3(const struct Vec3 *a, const struct Vec3 *b)
{
	struct Vec3 diff = sub_v3(a, b);
	return sqlen_v3(&diff);
}

static inline struct Vec3 lerp_v3(const struct Vec3 *a, const struct Vec3 *b,
				  float t)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.vec[i] = a->vec[i] + t * (b->vec[i] - a->vec[i]);
	return res;
}

static inline struct Vec3 proj_v3(const struct Vec3 *a, const struct Vec3 *b)
{
	struct Vec3 res = *b;
	float sqlen_b = sqlen_v3(b);

	if (likely(sqlen_b > 0.0f)) {
		float scal = dot_product_v3(a, b) / sqlen_b;
		mult_scal_v3(&res, scal);
	}
	return res;
}

static inline struct Vec3 reflect_v3(const struct Vec3 *v, const struct Vec3 *n)
{
	struct Vec3 res;
	float dot2 = 2.0f * dot_product_v3(v, n);

	for (int i = 0; i < 3; ++i)
		res.vec[i] = v->vec[i] - dot2 * n->vec[i];
	return res;
}

static inline struct Vec3 rotate_v3(const struct Vec3 *v,
				    const struct Quaternion *q);

#endif /* TARTARUS_LIN_ALGEBRA_VEC3_H */
