#ifndef TARTARUS_LIN_ALGEBRA_VEC2_H
#define TARTARUS_LIN_ALGEBRA_VEC2_H

#include <tartarus/compiler.h>
#include <tartarus/math.h>

/**
 * @brief Structure for a 3d vector. Uses an union to represent
 * the data in different ways.
 */
struct Vec2 {
	union {
		struct {
			float x, y;
		};
		float arr[2];
	};
};

/**
 * @brief Adds two vectors and returns the result.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return struct Vec2 		The result.
 */
static inline struct Vec2 add_v2(struct Vec2 a, struct Vec2 b)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
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
static inline struct Vec2 sub_v2(struct Vec2 a, struct Vec2 b)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
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
static inline struct Vec2 comp_mult_v2(struct Vec2 a, struct Vec2 b)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
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
static inline struct Vec2 comp_div_v2(struct Vec2 a, struct Vec2 b)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
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
static inline struct Vec2 mult_scal_v2(struct Vec2 x, float scalar)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
		res.arr[i] = x.arr[i] * scalar;
	return res;
}

/**
 * @brief Divides a vector with a scalar.
 *
 * @param x 		The vector to divide with.
 * @param scalar 	The scalar.
 * @return struct Vec2		The result.
 */
static inline struct Vec2 div_scal_v2(struct Vec2 x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	return mult_scal_v2(x, inv_scal);
}

/**
 * @brief Multiplies a vector with a scalar in place.
 *
 * @param x 		The vector to multiply with.
 * @param scalar 	The scalar.
 */
static inline void mult_scal_ip_v2(struct Vec2 *x, float scalar)
{
	for (int i = 0; i < 2; ++i)
		x->arr[i] *= scalar;
}

/**
 * @brief Divides a vector with a scalar in place.
 *
 * @param x 		The vector to divide with.
 * @param scalar 	The scalar.
 * @note The scalar cannot be 0.0f.
 */
static inline void div_scal_ip_v2(struct Vec2 *x, float scalar)
{
	float inv_scal = 1.0f / scalar;
	mult_scal_ip_v2(x, inv_scal);
}

/**
 * @brief Calculates the dot product of a and b and returns it.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The dot product.
 */
static inline float dot_product_v2(struct Vec2 a, struct Vec2 b)
{
	float res = 0.0f;
	for (int i = 0; i < 2; ++i)
		res += a.arr[i] * b.arr[i];
	return res;
}

/**
 * @brief Calculates the determinant of a and b.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The determinant.
 */
static inline float det_v2(struct Vec2 a, struct Vec2 b)
{
	return a.x * b.y - a.y * b.x;
}

/**
 * @brief Calculates the square lenght of a vector.
 *
 * @param x 		The vector.
 * @return float 	The square length.
 */
static inline float sqlen_v2(struct Vec2 x)
{
	return dot_product_v2(x, x);
}

/**
 * @brief Calculates the length of a vector.
 *
 * @param x 		The vector.
 * @return float 	The length.
 */
static inline float len_v2(struct Vec2 x)
{
	float sqsum = sqlen_v2(x);
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
static inline struct Vec2 norm_v2(struct Vec2 x)
{
	float len = len_v2(x);
	return div_scal_v2(x, len);
}

/**
 * @brief Normalizes a vector in place.
 *
 * @param x 		The vector to normalize.
 * @return struct Vec2 		The normalized vector.
 * @note The vector cannot have a length of 0.0f. No length checks
 * are carried out.
 */
static inline void norm_ip_v2(struct Vec2 *x)
{
	float len = len_v2(*x);
	if (likely(len > 0.0f))
		div_scal_ip_v2(x, len);
}

/**
 * @brief Calculates the distance between two vectors.
 *
 * @param a 		The first vector.
 * @param b 		The second vector.
 * @return float 	The distance.
 * @note A and b cannot be the same.
 */
static inline float dist_v2(struct Vec2 a, struct Vec2 b)
{
	struct Vec2 diff = sub_v2(a, b);
	return len_v2(diff);
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
static inline float sqdist_v2(struct Vec2 a, struct Vec2 b)
{
	struct Vec2 diff = sub_v2(a, b);
	return sqlen_v2(diff);
}

static inline struct Vec2 lerp_v2(struct Vec2 a, struct Vec2 b, float t)
{
	struct Vec2 res;
	for (int i = 0; i < 2; ++i)
		res.arr[i] = a.arr[i] + t * (b.arr[i] - a.arr[i]);
	return res;
}

static inline struct Vec2 proj_v2(struct Vec2 a, struct Vec2 b)
{
	struct Vec2 res = b;
	float sqlen_b = sqlen_v2(b);

	if (likely(sqlen_b > 0.0f)) {
		float scal = dot_product_v2(a, b) / sqlen_b;
		mult_scal_v2(res, scal);
	}
	return res;
}

static inline struct Vec2 reflect_v2(struct Vec2 v, struct Vec2 n)
{
	struct Vec2 res;
	float dot2 = 2.0f * dot_product_v2(v, n);

	for (int i = 0; i < 2; ++i)
		res.arr[i] = v.arr[i] - dot2 * n.arr[i];
	return res;
}

#endif /* TARTARUS_LIN_ALGEBRA_VEC2_H */
