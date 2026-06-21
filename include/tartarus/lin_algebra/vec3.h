#ifndef TARTARUS_LIN_ALGEBRA_VEC3_H
#define TARTARUS_LIN_ALGEBRA_VEC3_H

#include <tartarus/math.h>

struct Quaternion;

/**
 * @brief Structure for a 3d vector. Uses an union to represent the
 * data in different ways.
 */
struct Vec3 {
	union {
		struct {
			float x, y, z;
		};
		float arr[3];
	};
} __attribute__((packed));

/**
 * @brief Adds two vectors and returns the result.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec3 		The result.
 */
static inline struct Vec3 add_v3(struct Vec3 a, struct Vec3 b)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.arr[i] = a.arr[i] + b.arr[i];
	return res;
}

/**
 * @brief Subtracts vector a from b and returns the result.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec3 		The result.
 */
static inline struct Vec3 sub_v3(struct Vec3 a, struct Vec3 b)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.arr[i] = a.arr[i] - b.arr[i];
	return res;
}

/**
 * @brief Multiplies two vectors component wise and returns the
 * result.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec3 		The result.
 */
static inline struct Vec3 comp_mult_v3(struct Vec3 a, struct Vec3 b)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.arr[i] = a.arr[i] * b.arr[i];
	return res;
}

/**
 * @brief Divides a from b component wise and returns the result.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec3 		The result.
 * @note B cannot have a member with a value of 0.0f.
 */
static inline struct Vec3 comp_div_v3(struct Vec3 a, struct Vec3 b)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.arr[i] = a.arr[i] / b.arr[i];
	return res;
}

/**
 * @brief Mutliplies a vector with a scalar.
 *
 * @param x		The vector to multiply with.
 * @param scalar	The scalar.
 * @return struct Vec3		The result.
 */
static inline struct Vec3 mult_scal_v3(struct Vec3 x, float scalar)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
		res.arr[i] = x.arr[i] * scalar;
	return res;
}

/**
 * @brief Divides a vector with a scalar.
 *
 * @param x		The vector to divide with.
 * @param scalar	The scalar.
 * @return struct Vec3		The result.
 * @note The scaler cannot be 0.0f.
 */
static inline struct Vec3 div_scal_v3(struct Vec3 x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	return mult_scal_v3(x, inv_scal);
}

/**
 * @brief Multiplies a vector with a scalar in place.
 *
 * @param x 		The vector to multiply with.
 * @param scalar 	The scalar.
 */
static inline void mult_scal_ip_v3(struct Vec3 *x, float scalar)
{
	for (int i = 0; i < 3; ++i)
		x->arr[i] *= scalar;
}

/**
 * @brief Divides a vector with a scalar in place.
 *
 * @param x 		The vector to divide with.
 * @param scalar 	The scalar.
 * @note The scalar cannot be 0.0f.
 */
static inline void div_scal_ip_v3(struct Vec3 *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_ip_v3(x, inv_scal);
}

/**
 * @brief Calculates the dot product of a and b and returns it.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The dot product.
 */
static inline float dot_product_v3(struct Vec3 a, struct Vec3 b)
{
	float res = 0.0f;
	for (int i = 0; i < 3; ++i)
		res += a.arr[i] * b.arr[i];
	return res;
}

/**
 * @brief Calculates the cross product of a and b.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The cross product.
 */
static inline struct Vec3 cross_product_v3(struct Vec3 a, struct Vec3 b)
{
	struct Vec3 res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;

	return res;
}

/**
 * @brief Calculates the triple product of a, b and c.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @param c 		The third vector.
 * @return float	The triple product.
 */
static inline float triple_product_v3(struct Vec3 a, struct Vec3 b,
				      struct Vec3 c)
{
	struct Vec3 cross_prod = cross_product_v3(a, b);
	return dot_product_v3(cross_prod, c);
}

/**
 * @brief Calculates the square length of a vector (||v||^2).
 *
 * @param x 		The vector.
 * @return float 	The square length.
 */
static inline float sqlen_v3(struct Vec3 x)
{
	return dot_product_v3(x, x);
}

/**
 * @brief Calculates the length of a vector (||v||).
 *
 * @param x		The vector.
 * @return float	The lenght.
 */
static inline float len_v3(struct Vec3 x)
{
	float sqsum = sqlen_v3(x);
	return fsqrt(sqsum);
}

/**
 * @brief Normalizes a vector and returns it.
 *
 * @param x		The vector to normalize.
 * @return struct Vec3	The normalized vector.
 * @note The vector cannot have a length of 0.0f. The length will
 * not be checked to guarantee performance.
 */
static inline struct Vec3 norm_v3(struct Vec3 x)
{
	float len = len_v3(x);
	return div_scal_v3(x, len);
}

/**
 * @brief Normalizes a vector in place.
 *
 * @param x 		The vector to normalize.
 * @note The vector cannot have a length of 0.0f. The length will
 * not be checked to guarantee performance.
 */
static inline void norm_ip_v3(struct Vec3 *x)
{
	float len = len_v3(*x);
	div_scal_ip_v3(x, len);
}

/**
 * @brief Calculates the distance between a and b.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The distance.
 * @note A and b cannot be the same.
 */
static inline float dist_v3(struct Vec3 a, struct Vec3 b)
{
	struct Vec3 diff = sub_v3(a, b);
	return len_v3(diff);
}

/**
 * @brief Calculates the square distance between a and b.
 * Used for fast comparisons.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The distance.
 * @note A and b can be the same, the square distance becomes 0.0f.
 */
static inline float sqdist_v3(struct Vec3 a, struct Vec3 b)
{
	struct Vec3 diff = sub_v3(a, b);
	return sqlen_v3(diff);
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
static inline struct Vec3 lerp_v3(struct Vec3 a, struct Vec3 b, float t)
{
	struct Vec3 res;
	for (int i = 0; i < 3; ++i)
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
static inline struct Vec3 proj_v3(struct Vec3 a, struct Vec3 b)
{
	struct Vec3 res = b;
	float sqlen_b = sqlen_v3(b);

	if (likely(sqlen_b > 0.0f)) {
		float scal = dot_product_v3(a, b) / sqlen_b;
		mult_scal_v3(res, scal);
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
static inline struct Vec3 reflect_v3(struct Vec3 v, struct Vec3 n)
{
	struct Vec3 res;
	float dot2 = 2.0f * dot_product_v3(v, n);

	for (int i = 0; i < 3; ++i)
		res.arr[i] = v.arr[i] - dot2 * n.arr[i];
	return res;
}

static inline struct Vec3 rotate_v3(struct Vec3 v, struct Quaternion q);

#endif /* TARTARUS_LIN_ALGEBRA_VEC3_H */
