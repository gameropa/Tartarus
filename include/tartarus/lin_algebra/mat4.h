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

static inline struct Mat4 add_m4(struct Mat4 a, struct Mat4 b)
{
	struct Mat4 res;
	for (int i = 0; i < 16; ++i)
		res.arr[i] = a.arr[i] + b.arr[i];
	return res;
}

static inline struct Mat4 sub_m4(struct Mat4 a, struct Mat4 b)
{
	struct Mat4 res;
	for (int i = 0; i < 16; ++i)
		res.arr[i] = a.arr[i] - b.arr[i];
	return res;
}

static inline struct Mat4 comp_mult_m4(struct Mat4 a, struct Mat4 b)
{
	struct Mat4 res;
	for (int i = 0; i < 16; ++i)
		res.arr[i] = a.arr[i] * b.arr[i];
	return res;
}

static inline struct Mat4 comp_div_m4(struct Mat4 a, struct Mat4 b)
{
	struct Mat4 res;
	for (int i = 0; i < 16; ++i)
		res.arr[i] = a.arr[i] / b.arr[i];
	return res;
}

static inline struct Mat4 mult_scal_m4(struct Mat4 x, float scalar)
{
	struct Mat4 res;
	for (int i = 0; i < 16; ++i)
		res.arr[i] = x.arr[i] * scalar;
	return res;
}

static inline struct Mat4 div_scal_m4(struct Mat4 x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	return mult_scal_m4(x, inv_scal);
}

static inline void mult_scal_ip_m4(struct Mat4 *x, float scalar)
{
	for (int i = 0; i < 16; ++i)
		x->arr[i] *= scalar;
}

static inline void div_scal_ip_m4(struct Mat4 *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_ip_m4(x, inv_scal);
}

static inline struct Mat4 ident_m4(void)
{
	return (struct Mat4){ .right = { { { 1.0f, 0.0f, 0.0f, 0.0f } } },
			      .up = { { { 0.0f, 1.0f, 0.0f, 0.0f } } },
			      .forw = { { { 0.0f, 0.0f, 1.0f, 0.0f } } },
			      .pos = { { { 0.0f, 0.0f, 0.0f, 1.0f } } } };
}

static inline struct Vec4 mult_m4_v4(struct Mat4 m, struct Vec4 v)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = m.right.arr[i] * v.x + m.up.arr[i] * v.y +
			     m.forw.arr[i] * v.z + m.pos.arr[i] * v.w;
	return res;
}

extern void mult_m4(struct Mat4 *restrict out, const struct Mat4 *restrict a,
		    const struct Mat4 *restrict b);

extern void fast_mult_m4(struct Mat4 *restrict out,
			 const struct Mat4 *restrict transp_a,
			 const struct Mat4 *restrict b);

#endif /* TARTARUS_LIN_ALGEBRA_MAT4_H */
