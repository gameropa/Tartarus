#ifndef TARTARUS_LIN_ALGEBRA_QUATERNION_H
#define TARTARUS_LIN_ALGEBRA_QUATERNION_H

#include <tartarus/compiler.h>
#include <tartarus/math.h>
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

static inline struct Quaternion ident_quat(void)
{
	struct Quaternion res;
	res.w = 1.0f;
	res.i = res.j = res.k = 0.0f;
	return res;
}

static inline struct Quaternion add_quat(const struct Quaternion *a,
					 const struct Quaternion *b)
{
	struct Quaternion res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a->arr[i] + b->arr[i];
	return res;
}

static inline struct Quaternion sub_quat(const struct Quaternion *a,
					 const struct Quaternion *b)
{
	struct Quaternion res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a->arr[i] - b->arr[i];
	return res;
}

static inline void mult_scal_quat(struct Quaternion *x, float scalar)
{
	for (int i = 0; i < 4; ++i)
		x->arr[i] *= scalar;
}

static inline void div_scal_quat(struct Quaternion *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_quat(x, inv_scal);
}

static inline float dot_product_quat(const struct Quaternion *a,
				     const struct Quaternion *b)
{
	float res = 0.0f;
	for (int i = 0; i < 4; ++i)
		res += a->arr[i] * b->arr[i];
	return res;
}

static inline struct Quaternion mult_quat(const struct Quaternion *a,
					  const struct Quaternion *b)
{
	struct Quaternion res;
	res.scal = a->scal * b->scal - dot_product_v3(&a->vec, &b->vec);

	struct Vec3 cross = cross_product_v3(&a->vec, &b->vec);

	for (int i = 0; i < 3; ++i)
		res.vec.vec[i] = (a->scal * b->vec.vec[i]) +
				 (b->scal * a->vec.vec[i]) + cross.vec[i];
	return res;
}

static inline float sqlen_quat(const struct Quaternion *x)
{
	return dot_product_quat(x, x);
}

static inline float len_quat(const struct Quaternion *x)
{
	float sqsum = sqlen_quat(x);
	return fsqrt(sqsum);
}

static inline void norm_quat(struct Quaternion *x)
{
	float len = len_quat(x);
	if (likely(len > 0.0f))
		div_scal_quat(x, len);
}

static inline struct Quaternion conj_quat(const struct Quaternion *x)
{
	struct Quaternion res;
	res.w = x->w;
	res.i = -x->i;
	res.j = -x->j;
	res.k = -x->k;
	return res;
}

static inline struct Quaternion inv_quat(const struct Quaternion *x)
{
	struct Quaternion res = conj_quat(x);
	float sqlen = sqlen_quat(x);

	if (likely(sqlen > 0.0f))
		div_scal_quat(&res, sqlen);
	return res;
}

static inline struct Vec3 rotate_v3(const struct Vec3 *v,
				    const struct Quaternion *q)
{
	struct Vec3 qv = q->vec;
	struct Vec3 uv = cross_product_v3(&qv, v);
	struct Vec3 uuv = cross_product_v3(&qv, &uv);

	for (int i = 0; i < 3; ++i)
		uv.vec[i] = (uv.vec[i] * q->scal + uuv.vec[i]) * 2.0f;

	return add_v3(v, &uv);
}

/**
 * @brief Creates a rotation quaternion from an axis and an angle.
 *
 * @param axis 		The rotation axis. The axis MUST be normalized.
 * @param angle		The rotation angle in radians.
 * @return struct Quaternion	The rotation quaternion.
 */
static inline struct Quaternion rotquat_axis_angle(const struct Vec3 *axis,
						   float angle)
{
	struct Quaternion res;
	float half_ang = angle * 0.5f;
	float sin_half = fsin(half_ang);

	res.scal = fcos(half_ang);
	for (int i = 0; i < 3; ++i)
		res.vec.vec[i] = axis->vec[i] * sin_half;

	return res;
}

static inline struct Quaternion rotquat_xaxis(float angle)
{
	struct Quaternion res;
	float half_ang = angle * 0.5f;

	res.w = fcos(half_ang);
	res.i = fsin(half_ang);
	res.j = 0.0f;
	res.k = 0.0f;

	return res;
}

static inline struct Quaternion rotquat_yaxis(float angle)
{
	struct Quaternion res;
	float half_ang = angle * 0.5f;

	res.w = fcos(half_ang);
	res.i = 0.0f;
	res.j = fsin(half_ang);
	res.k = 0.0f;

	return res;
}

static inline struct Quaternion rotquat_zaxis(float angle)
{
	struct Quaternion res;
	float half_ang = angle * 0.5f;

	res.w = fcos(half_ang);
	res.i = 0.0f;
	res.j = 0.0f;
	res.k = fsin(half_ang);

	return res;
}

#endif /* TARTARUS_LIN_ALGEBRA_QUATERNION_H */
