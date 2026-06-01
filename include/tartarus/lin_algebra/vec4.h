#ifndef TARTARUS_LIN_ALGEBRA_VEC4_H
#define TARTARUS_LIN_ALGEBRA_VEC4_H

#include <tartarus/lin_algebra/vec3.h>
#include <tartarus/compiler.h>
#include <tartarus/math.h>

struct Vec4 {
	union {
		struct {
			float x, y, z, w;
		};
		float vec[4];
	};
} __attribute__((aligned(16)));

static inline struct Vec4 add_v4(const struct Vec4 *a, const struct Vec4 *b)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.vec[i] = a->vec[i] + b->vec[i];
	return res;
}

static inline struct Vec4 sub_v4(const struct Vec4 *a, const struct Vec4 *b)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.vec[i] = a->vec[i] - b->vec[i];
	return res;
}

static inline struct Vec4 comp_mult_v4(const struct Vec4 *a,
				       const struct Vec4 *b)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.vec[i] = a->vec[i] * b->vec[i];
	return res;
}

static inline struct Vec4 comp_div_v4(const struct Vec4 *a,
				      const struct Vec4 *b)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.vec[i] = a->vec[i] / b->vec[i];
	return res;
}

static inline void mult_scal_v4(struct Vec4 *x, float scalar)
{
	for (int i = 0; i < 4; ++i)
		x->vec[i] *= scalar;
}

static inline void div_scal_v4(struct Vec4 *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_v4(x, inv_scal);
}

static inline float dot_product_v4(const struct Vec4 *a, const struct Vec4 *b)
{
	float res = 0.0f;
	for (int i = 0; i < 4; ++i)
		res += a->vec[i] * b->vec[i];
	return res;
}

static inline float sqlen_v4(const struct Vec4 *x)
{
	return dot_product_v4(x, x);
}

static inline float len_v4(const struct Vec4 *x)
{
	float sqsum = sqlen_v4(x);
	return fsqrt(sqsum);
}

static inline void norm_v4(struct Vec4 *x)
{
	float len = len_v4(x);
	if (likely(len > 0.0f))
		div_scal_v4(x, len);
}

static inline float dist_v4(const struct Vec4 *a, const struct Vec4 *b)
{
	struct Vec4 diff = sub_v4(a, b);
	return len_v4(&diff);
}

static inline float sqdist_v4(const struct Vec4 *a, const struct Vec4 *b)
{
	struct Vec4 diff = sub_v4(a, b);
	return sqlen_v4(&diff);
}

static inline struct Vec4 lerp_v4(const struct Vec4 *a, const struct Vec4 *b,
				  float t)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.vec[i] = a->vec[i] + t * (b->vec[i] - a->vec[i]);
	return res;
}

static inline struct Vec4 proj_v4(const struct Vec4 *a, const struct Vec4 *b)
{
	struct Vec4 res = *b;
	float sqlen_b = sqlen_v4(b);

	if (likely(sqlen_b > 0.0f)) {
		float scal = dot_product_v4(a, b) / sqlen_b;
		mult_scal_v4(&res, scal);
	}
	return res;
}

static inline struct Vec4 reflect_v4(const struct Vec4 *v, const struct Vec4 *n)
{
	struct Vec4 res;
	float dot2 = 2.0f * dot_product_v4(v, n);

	for (int i = 0; i < 4; ++i)
		res.vec[i] = v->vec[i] - dot2 * n->vec[i];
	return res;
}

static inline void perspective_div_v4(struct Vec4 *x)
{
	if (likely(x->w != 0.0f)) {
		float inv_w = 1.0f / x->w;
		x->x *= inv_w;
		x->y *= inv_w;
		x->z *= inv_w;
		x->w = 1.0f;
	}
}

static inline struct Vec4 vec3_to_point(const struct Vec3 *v)
{
	struct Vec4 res;
	res.x = v->x;
	res.y = v->y;
	res.z = v->z;
	res.w = 1.0f;
	return res;
}

static inline struct Vec4 vec3_to_dir(const struct Vec3 *v)
{
	struct Vec4 res;
	res.x = v->x;
	res.y = v->y;
	res.z = v->z;
	res.w = 0.0f;
	return res;
}

#endif /* TARTARUS_LIN_ALGEBRA_VEC4_H */
