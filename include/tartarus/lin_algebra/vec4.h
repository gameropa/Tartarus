#ifndef TARTARUS_LIN_ALGEBRA_VEC4_H
#define TARTARUS_LIN_ALGEBRA_VEC4_H

#include <tartarus/lin_algebra/vec3.h>
#include <tartarus/compiler.h>
#include <tartarus/math.h>

/**
 * @brief Structure for a 4d vector. Uses union to represent
 * the data in different ways.
 */
struct Vec4 {
	union {
		struct {
			float x, y, z, w;
		};
		float arr[4];
	};
} __attribute__((aligned(16)));

/**
 * @brief Adds two vectors and returns the result.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec2 		The result.
 */
static inline struct Vec4 add_v4(struct Vec4 a, struct Vec4 b)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a.arr[i] + b.arr[i];
	return res;
}

/**
 * @brief Subtracts a from b and returns the difference.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec2 		The difference.
 */
static inline struct Vec4 sub_v4(struct Vec4 a, struct Vec4 b)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a.arr[i] - b.arr[i];
	return res;
}

/**
 * @brief Multiplies two vectors component wise and returns the result.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec2 		The result.
 */
static inline struct Vec4 comp_mult_v4(struct Vec4 a, struct Vec4 b)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a.arr[i] * b.arr[i];
	return res;
}

/**
 * @brief Divides a from b component wise and returns the result.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec2 		The result.
 */
static inline struct Vec4 comp_div_v4(struct Vec4 a, struct Vec4 b)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a.arr[i] / b.arr[i];
	return res;
}

/**
 * @brief Multplies a vector with a scalar.
 *
 * @param x 		The vector to multiply with.
 * @param scalar 	The scalar.
 * @return struct Vec2		The result.
 */
static inline struct Vec4 mult_scal_v4(struct Vec4 x, float scalar)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = x.arr[i] = scalar;
	return res;
}

/**
 * @brief Divides a vector with a scalar.
 *
 * @param x 		The vector to divide with.
 * @param scalar 	The scalar.
 * @return struct Vec2		The result.
 */
static inline struct Vec4 div_scal_v4(struct Vec4 x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	return mult_scal_v4(x, inv_scal);
}

/**
 * @brief Multiplies a vector with a scalar in place.
 *
 * @param x 		The vector to multiply with.
 * @param scalar 	The scalar.
 */
static inline void mult_scal_ip_v4(struct Vec4 *x, float scalar)
{
	for (int i = 0; i < 4; ++i)
		x->arr[i] *= scalar;
}

/**
 * @brief Divides a vector with a scalar in place.
 *
 * @param x 		The vector to divide with.
 * @param scalar 	The scalar.
 * @note The scalar cannot be 0.0f.
 */
static inline void div_scal_ip_v4(struct Vec4 *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_ip_v4(x, inv_scal);
}

/**
 * @brief Calculates the dot product of a and b and returns it.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The dot product.
 */
static inline float dot_product_v4(struct Vec4 a, struct Vec4 b)
{
	float res = 0.0f;
	for (int i = 0; i < 4; ++i)
		res += a.arr[i] * b.arr[i];
	return res;
}

/**
 * @brief Calculates the square lenght of a vector.
 *
 * @param x 		The vector.
 * @return float 	The square length.
 */
static inline float sqlen_v4(struct Vec4 x)
{
	return dot_product_v4(x, x);
}

/**
 * @brief Calculates the length of a vector.
 *
 * @param x 		The vector.
 * @return float 	The length.
 */
static inline float len_v4(struct Vec4 x)
{
	float sqsum = sqlen_v4(x);
	return fsqrt(sqsum);
}

/**
 * @brief Normalizes a vector and returns the result.
 *
 * @param x 		The vector to normalize.
 * @return struct Vec2 		The normalized vector.
 * @note The vector cannot have a length of 0.0f. No length checks
 * are carried out.
 */
static inline struct Vec4 norm_v4(struct Vec4 x)
{
	float len = len_v4(x);
	return div_scal_v4(x, len);
}

/**
 * @brief Normalizes a vector in place.
 *
 * @param x 		The vector to normalize.
 * @return struct Vec2 		The normalized vector.
 * @note The vector cannot have a length of 0.0f. No length checks
 * are carried out.
 */
static inline void norm_ip_v4(struct Vec4 *x)
{
	float len = len_v4(*x);
	div_scal_ip_v4(x, len);
}

/**
 * @brief Calculates the distance between two vectors.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The distance.
 * @note A and b cannot be the same.
 */
static inline float dist_v4(struct Vec4 a, struct Vec4 b)
{
	struct Vec4 diff = sub_v4(a, b);
	return len_v4(diff);
}

/**
 * @brief Calculates the square distance between two vectors.
 * Can be used for fast comparisons.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The distance.
 * @note A and b can be the same, the square distance becomes 0.0f.
 */
static inline float sqdist_v4(struct Vec4 a, struct Vec4 b)
{
	struct Vec4 diff = sub_v4(a, b);
	return sqlen_v4(diff);
}

/**
 * @brief Linear interpolation. Calculates a position between a and b.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @param t 		The interpolation factor. Must be between 0 (Point is on a)
 * 			and 1 (Point is on b).
 * @return struct Vec4 		The point between a and b.
 */
static inline struct Vec4 lerp_v4(struct Vec4 a, struct Vec4 b, float t)
{
	struct Vec4 res;
	for (int i = 0; i < 4; ++i)
		res.arr[i] = a.arr[i] + t * (b.arr[i] - a.arr[i]);
	return res;
}

/**
 * @brief Projects a on b. The result points in the same or opposite direction
 * as b. The result has a maximum length of b.
 *
 * @param a 		The vector to project.
 * @param b 		The vector to project on.
 * @return struct Vec4 		The projected vector.
 */
static inline struct Vec4 proj_v4(struct Vec4 a, struct Vec4 b)
{
	struct Vec4 res = b;
	float sqlen_b = sqlen_v4(b);

	if (likely(sqlen_b > 0.0f)) {
		float scal = dot_product_v4(a, b) / sqlen_b;
		mult_scal_v4(res, scal);
	}
	return res;
}

/**
 * @brief Reflects v on n.
 *
 * @param v 		The incident vector to reflect (Pointing towards the surface).
 * @param n		The surface normal vector.
 * @return struct Vec4		The reflected vector.
 * @note N must be normalized, otherwise the result will be incorrect. Also assumes
 * v points to the surface.
 */
static inline struct Vec4 reflect_v4(struct Vec4 v, struct Vec4 n)
{
	struct Vec4 res;
	float dot2 = 2.0f * dot_product_v4(v, n);

	for (int i = 0; i < 4; ++i)
		res.arr[i] = v.arr[i] - dot2 * n.arr[i];
	return res;
}

/**
 * @brief Performs perspective division on x. Divides x, y and z by w from clip space.
 * into NDC.
 *
 * @param x		Pointer to 4D vector.
 * @return struct Vec4		Transformed vector.
 * @note If w is 0.0f, the vector remains unchanged to prevent division by zero.
 * Sets w to 1.0f, because w/w = 1.
 */
static inline struct Vec4 perspective_div_v4(struct Vec4 x)
{
	struct Vec4 res = x;
	if (likely(x.w != 0.0f)) {
		float inv_w = 1.0f / x.w;
		res.x *= inv_w;
		res.y *= inv_w;
		res.z *= inv_w;
		res.w = 1.0f;
	}
	return res;
}

/**
 * @brief Transforms a 3D vector into a 4D point and sets w to 1.0f.
 *
 * @param v 		The 3D vector.
 * @return struct Vec4 		The 4D point.
 */
static inline struct Vec4 vec3_to_point(const struct Vec3 v)
{
	struct Vec4 res;
	res.x = v.x;
	res.y = v.y;
	res.z = v.z;
	res.w = 1.0f;
	return res;
}

/**
 * @brief Transforms a 3D vector into a 4D direction and sets w to 0.0f.
 *
 * @param v		The 3D vector.
 * @return struct Vec4		The 4D direction.
 */
static inline struct Vec4 vec3_to_dir(const struct Vec3 v)
{
	struct Vec4 res;
	res.x = v.x;
	res.y = v.y;
	res.z = v.z;
	res.w = 0.0f;
	return res;
}

#endif /* TARTARUS_LIN_ALGEBRA_VEC4_H */
