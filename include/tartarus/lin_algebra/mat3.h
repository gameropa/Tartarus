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

static inline struct Mat3 add_m3(struct Mat3 a, struct Mat3 b)
{
	struct Mat3 res;
	for (int i = 0; i < 9; ++i)
		res.arr[i] = a.arr[i] + b.arr[i];
	return res;
}

static inline struct Mat3 sub_m3(struct Mat3 a, struct Mat3 b)
{
	struct Mat3 res;
	for (int i = 0; i < 9; ++i)
		res.arr[i] = a.arr[i] - b.arr[i];
	return res;
}

static inline struct Mat3 comp_mult_m3(struct Mat3 a, struct Mat3 b)
{
	struct Mat3 res;
	for (int i = 0; i < 9; ++i)
		res.arr[i] = a.arr[i] * b.arr[i];
	return res;
}

static inline struct Mat3 comp_div_m3(struct Mat3 a, struct Mat3 b)
{
	struct Mat3 res;
	for (int i = 0; i < 9; ++i)
		res.arr[i] = a.arr[i] / b.arr[i];
	return res;
}

static inline struct Mat3 mult_scal_m3(struct Mat3 x, float scalar)
{
	struct Mat3 res;
	for (int i = 0; i < 9; ++i)
		res.arr[i] = x.arr[i] * scalar;
	return res;
}

static inline struct Mat3 div_scal_m3(struct Mat3 x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	return mult_scal_m3(x, inv_scal);
}

static inline void mult_scal_ip_m3(struct Mat3 *x, float scalar)
{
	for (int i = 0; i < 9; ++i)
		x->arr[i] *= scalar;
}

static inline void div_scal_ip_m3(struct Mat3 *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_ip_m3(x, inv_scal);
}

static inline struct Mat3 ident_m3(void)
{
	return (struct Mat3){ .right = { { { 1.0f, 0.0f, 0.0f } } },
			      .up = { { { 0.0f, 1.0f, 0.0f } } },
			      .forw = { { { 0.0f, 0.0f, 1.0f } } } };
}

static inline struct Vec3 mult_m3_v3(struct Mat3 m, struct Vec3 v)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.arr[i] = m.right.arr[i] * v.x + m.up.arr[i] * v.y +
			     m.forw.arr[i] * v.z;
	return res;
}

extern void mult_m3(struct Mat3 *restrict out, const struct Mat3 *restrict a,
		    const struct Mat3 *restrict b);

extern void fast_mult_m3(struct Mat3 *restrict out,
			 const struct Mat3 *restrict transp_a,
			 const struct Mat3 *restrict b);

#endif /* TARTARUS_LIN_ALGEBRA_MAT3_H */
