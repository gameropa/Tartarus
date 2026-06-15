#ifndef TARTARUS_LIN_ALGEBRA_QUATERNION_H
#define TARTARUS_LIN_ALGEBRA_QUATERNION_H

#include <tartarus/math.h>
#include <tartarus/lin_algebra/vec3.h>

/**
 * @brief Structure for a quaternion. We are using a union here to access the
 * data in different ways.
 */
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

/**
 * @brief Creates a identity quaternion with a length of one.
 *
 * @return struct Quaternion 	The idenetity quaternions.
 */
static inline struct Quaternion ident_quat(void)
{
	struct Quaternion res;
	res.w = 1.0f;
	res.i = res.j = res.k = 0.0f;
	return res;
}

/**
 * @brief Adds two quaternions and returns a new one.
 *
 * @param a 		The first quaternion.
 * @param b 		The second quaternion.
 * @return struct Quaternion 		The sum.
 */
static inline struct Quaternion add_quat(struct Quaternion a,
					 struct Quaternion b)
{
	struct Quaternion res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a.arr[i] + b.arr[i];
	return res;
}

/**
 * @brief Subtracts quaternion b from a.
 *
 * @param a		The first quaternion.
 * @param b		The second quaternion.
 * @return struct Quaternion		The difference.
 */
static inline struct Quaternion sub_quat(struct Quaternion a,
					 struct Quaternion b)
{
	struct Quaternion res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a.arr[i] - b.arr[i];
	return res;
}

/**
 * @brief Multiplies a quaternion with a scalar and returns a new one.
 *
 * @param x 		The quaternion to multiply with.
 * @param scalar 	The scalar.
 * @return struct Quaternion 		The product.
 */
static inline struct Quaternion mult_scal_quat(struct Quaternion x,
					       float scalar)
{
	struct Quaternion res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = x.arr[i] * scalar;
	return res;
}

/**
 * @brief Divides the quaternion from the scalar.
 *
 * @param x 		The quaternion to divide with.
 * @param scalar 	The scalar.
 * @return struct Quaternion 		The quotient.
 * @note The scalar cannot be 0.0f
 */
static inline struct Quaternion div_scal_quat(struct Quaternion x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	return mult_scal_quat(x, inv_scal);
}

/**
 * @brief Multiplies a quaternion with a scalar in place.
 *
 * @param x 		The quaternion to multiply with.
 * @param scalar 	The scalar.
 */
static inline void mult_scal_ip_quat(struct Quaternion *x, float scalar)
{
	for (int i = 0; i < 4; ++i)
		x->arr[i] *= scalar;
}

/**
 * @brief Divides a quaternion with a scalar in place.
 *
 * @param x 		The quaternion to divide with.
 * @param scalar 	The scalar.
 * @note The scalar cannot be 0.0f
 */
static inline void div_scal_ip_quat(struct Quaternion *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_ip_quat(x, inv_scal);
}

/**
 * @brief Calculates the dot product of a and b.
 *
 * @param a 		The first quaternion.
 * @param b 		The second quaternion.
 * @return float 	The dot product.
 */
static inline float dot_product_quat(struct Quaternion a, struct Quaternion b)
{
	float res = 0.0f;
	for (int i = 0; i < 4; ++i)
		res += a.arr[i] * b.arr[i];
	return res;
}

/**
 * @brief Multiplies two quaternions.
 *
 * @param a 		The first quaternion.
 * @param b 		The second quaternion.
 * @return struct Quaternion 	The result.
 */
static inline struct Quaternion mult_quat(struct Quaternion a,
					  struct Quaternion b)
{
	struct Quaternion res;
	res.scal = a.scal * b.scal - dot_product_v3(a.vec, b.vec);

	struct Vec3 cross = cross_product_v3(a.vec, b.vec);

	for (int i = 0; i < 3; ++i)
		res.vec.arr[i] = (a.scal * b.vec.arr[i]) +
				 (b.scal * a.vec.arr[i]) + cross.arr[i];
	return res;
}

/**
 * @brief Calculates the square length of a quaternion (||q||^2).
 *
 * @param x 		The quaternion.
 * @return float	The square length.
 */
static inline float sqlen_quat(struct Quaternion x)
{
	return dot_product_quat(x, x);
}

/**
 * @brief Calculates the length of a quaternion (||q||).
 *
 * @param x		The quaternion.
 * @return float	The length.
 */
static inline float len_quat(struct Quaternion x)
{
	float sqsum = sqlen_quat(x);
	return fsqrt(sqsum);
}

/**
 * @brief Normalizes a quaternion and returns a new one.
 *
 * @param x 		The quaternion.
 * @return struct Quaternion	The normalizes quaternion.
 * @note The length of the quaternion cannot be 0.0f, otherwise this
 * function will break. There is no lenght check for performance reasons.
 */
static inline struct Quaternion norm_quat(struct Quaternion x)
{
	float len = len_quat(x);
	return div_scal_quat(x, len);
}

/**
 * @brief Normalizes a quaternion in place.
 *
 * @param x 		The quaternion.
 * @note The length of the quaternion cannot be 0.0f, otherwise this
 * function will break. There is no lenght check for performance reasons.
 */
static inline void norm_ip_quat(struct Quaternion *x)
{
	float len = len_quat(*x);
	div_scal_ip_quat(x, len);
}

/**
 * @brief Conjugates a quaternion and returns the result.
 *
 * @param x 		The quaternion.
 * @return struct Quaternion 	The conjugate.
 */
static inline struct Quaternion conj_quat(struct Quaternion x)
{
	struct Quaternion res;
	res.w = x.w;
	res.i = -x.i;
	res.j = -x.j;
	res.k = -x.k;
	return res;
}

/**
 * @brief Inverts a quaternion and returns the result.
 *
 * @param x 		The quaternion.
 * @return struct Quaternion 	The inverse.
 * @note The length of the quaternion cannot be 0.0f, otherwise this
 * function will break. There is no lenght check for performance reasons.
 */
static inline struct Quaternion inv_quat(struct Quaternion x)
{
	struct Quaternion res = conj_quat(x);
	float sqlen = sqlen_quat(x);
	div_scal_ip_quat(&res, sqlen);
	return res;
}

/**
 * @brief Rotates a 3d vector using a rotation quaternion. Returns the result.
 *
 * @param v		The vector to rotate.
 * @param q		The rotation quaternion.
 * @return struct Vec3		The rotated vector.
 * @note The quaternion must be normalized, otherwise the rotation won't work
 * as intendet.
 */
static inline struct Vec3 rotate_v3(struct Vec3 v, struct Quaternion q)
{
	struct Vec3 qv = q.vec;
	struct Vec3 uv = cross_product_v3(qv, v);
	struct Vec3 uuv = cross_product_v3(qv, uv);

	for (int i = 0; i < 3; ++i)
		uv.arr[i] = (uv.arr[i] * q.scal + uuv.arr[i]) * 2.0f;

	return add_v3(v, uv);
}

/**
 * @brief Creates a rotation quaternion from an axis and an angle. The quaternion
 * is normalized.
 *
 * @param axis 		The rotation axis. The axis MUST be normalized.
 * @param angle		The rotation angle in radians.
 * @return struct Quaternion	The normalized rotation quaternion.
 * @note The axis must be normalized to create a valid rotation quaternion.
 */
static inline struct Quaternion rotquat_axis_angle(struct Vec3 axis,
						   float angle)
{
	struct Quaternion res;
	float half_ang = angle * 0.5f;
	float sin_half = fsin(half_ang);

	res.scal = fcos(half_ang);
	for (int i = 0; i < 3; ++i)
		res.vec.arr[i] = axis.arr[i] * sin_half;

	return res;
}

/**
 * @brief Creates a rotation quaternion rotating around the x-axis in a certain
 * angle.
 *
 * @param angle		The rotation angle in radians.
 * @return struct Quaternion	The normalized rotation quaternion.
 */
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

/**
 * @brief Creates a rotation quaternion rotating around the y-axis in a certain
 * angle.
 *
 * @param angle		The rotation angle in radians.
 * @return struct Quaternion	The normalized rotation quaternion.
 */
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

/**
 * @brief Creates a rotation quaternion rotating around the z-axis in a certain
 * angle.
 *
 * @param angle		The rotation angle in radians.
 * @return struct Quaternion	The normalized rotation quaternion.
 */
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
