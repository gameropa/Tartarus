#ifndef TARTARUS_LIN_ALGEBRA_VEC2_H
#define TARTARUS_LIN_ALGEBRA_VEC2_H

#include <tartarus/compiler.h>
#include <tartarus/math.h>

struct Vec2 {
	union {
		struct {
			float x, y;
		};
		float vec[2];
	};
};

static inline struct Vec2 add_v2(const struct Vec2 *a, const struct Vec2 *b)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
		res.vec[i] = a->vec[i] + b->vec[i];
	return res;
}

static inline struct Vec2 sub_v2(const struct Vec2 *a, const struct Vec2 *b)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
		res.vec[i] = a->vec[i] - b->vec[i];
	return res;
}

static inline struct Vec2 comp_mult_v2(const struct Vec2 *a,
				       const struct Vec2 *b)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
		res.vec[i] = a->vec[i] * b->vec[i];
	return res;
}

static inline struct Vec2 comp_div_v2(const struct Vec2 *a,
				      const struct Vec2 *b)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
		res.vec[i] = a->vec[i] / b->vec[i];
	return res;
}

static inline void mult_scal_v2(struct Vec2 *x, float scalar)
{
	for (int i = 0; i < 2; ++i)
		x->vec[i] *= scalar;
}

static inline void div_scal_v2(struct Vec2 *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_v2(x, inv_scal);
}

static inline float dot_product_v2(const struct Vec2 *a, const struct Vec2 *b)
{
	float res = 0.0f;
	for (int i = 0; i < 2; ++i)
		res += a->vec[i] * b->vec[i];
	return res;
}

static inline float det_v2(const struct Vec2 *a, const struct Vec2 *b)
{
	return a->x * b->y - a->y * b->x;
}

static inline float sqlen_v2(const struct Vec2 *x)
{
	return dot_product_v2(x, x);
}

static inline float len_v2(const struct Vec2 *x)
{
	float sqsum = sqlen_v2(x);
	return fsqrt(sqsum);
}

static inline void norm_v2(struct Vec2 *x)
{
	float len = len_v2(x);
	if (likely(len > 0.0f))
		div_scal_v2(x, len);
}

static inline float dist_v2(const struct Vec2 *a, const struct Vec2 *b)
{
	struct Vec2 diff = sub_v2(a, b);
	return len_v2(&diff);
}

static inline float sqdist_v2(const struct Vec2 *a, const struct Vec2 *b)
{
	struct Vec2 diff = sub_v2(a, b);
	return sqlen_v2(&diff);
}

static inline struct Vec2 lerp_v2(const struct Vec2 *a, const struct Vec2 *b,
				  float t)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
		res.vec[i] = a->vec[i] + t * (b->vec[i] - a->vec[i]);
	return res;
}

static inline struct Vec2 proj_v2(const struct Vec2 *a, const struct Vec2 *b)
{
	struct Vec2 res = *b;
	float sqlen_b = sqlen_v2(b);

	if (likely(sqlen_b > 0.0f)) {
		float scal = dot_product_v2(a, b) / sqlen_b;
		mult_scal_v2(&res, scal);
	}
	return res;
}

static inline struct Vec2 reflect_v2(const struct Vec2 *v, const struct Vec2 *n)
{
	struct Vec2 res;
	float dot2 = 2.0f * dot_product_v2(v, n);

	for (int i = 0; i < 2; ++i)
		res.vec[i] = v->vec[i] - dot2 * n->vec[i];
	return res;
}

#endif /* TARTARUS_LIN_ALGEBRA_VEC2_H */
