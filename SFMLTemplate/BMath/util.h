/*
	Math Utility
	By Dan Buckstein
	Basic helper functions for math stuff, like linear interpolation, random 
		number generation, and more to come.

	USER DEFINES: 
		_BMATH_LERP_ALT			use an alternative definition for LERP: 
								default is ( (1-t)p0 + (t)p1 )
								alternate is ( p0 + (t)(p1-p0) )
*/


#ifndef _BMATH_UTIL_H
#define _BMATH_UTIL_H


#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include <stdlib.h>
#include <string.h>


namespace bmath
{
namespace util
{


// random number generators
	// generates a random number between [minv, maxv]
float random(const float minv, const float maxv);
	// generates a random number between [ 0, 1] (normalized)
float randomNorm();
	// generates a random number between [-1, 1] (symmetric normalized)
float randomSymm();


// statistical formulas and utilities
	// produce the summation of 1 to n
unsigned int summation(unsigned int n);
float summationf(unsigned int n);

	// produce the factorial of n (n!)
unsigned int factorial(unsigned int n);
float factorialf(unsigned int n);

	// compute the permutation of n permute k
unsigned int permutation(unsigned int n, unsigned int k);
float permutationf(unsigned int n, unsigned int k);

	// compute the combination of n choose k
unsigned int combination(unsigned int n, unsigned int k);
float combinationf(unsigned int n, unsigned int k);


// operations

	// transform interpolation parameters for easing
float easeInParam(float t);
float easeOutParam(float t);


	// safe division: prevents 'NaN' results by returning zero if the denominator is zero
float divide(const float numerator, const float denominator);


	// stand-in linear operations for floats
float absVal(const float n);
float sign(const float n);
float dot(const float n0, const float n1);
float length(const float n);
float normalize(const float n);

	// linear algebra operations
template <typename type>
float length(const type n);
template <typename type>
float lengthSq(const type n);
template <typename type>
float invLength(const type n);
template <typename type>
float invLengthSq(const type n);
template <typename type>
type normalize(const type n);
template <typename type>
float projScalar(const type n, const type onto);
template <typename type>
type proj(const type n, const type onto);


	// get the reciprocal of something (if the divide operator exists)
template <typename type>
type recip(const type n);

	// clamp value between specified min and max
template <typename type>
type clamp(const type value, const type minimum, const type maximum);

	// return linear interpolation between n0 and n1 at time t
template <typename type>
type lerp(const type n0, const type n1, const float t);

	// inverse of lerp: get the interpolation parameter 't' given minimum, maximum and value
template <typename type>
float invLerp(const type n0, const type n1, const type value);
template <typename type>
void invLerp(const type n0, const type n1, const type value, float &t);


// constants
#define deg2rad		0.01745329251994329576923690768489
#define rad2deg		57.295779513082320876798154814105
#define twopi		6.283185307179586476925286766559
#define invRandMax	3.0518509475997192297128208258309e-5

#define deg2radf	0.01745329251994329576923690768489f
#define rad2degf	57.295779513082320876798154814105f
#define twopif		6.283185307179586476925286766559f
#define invRandMaxf	3.0518509475997192297128208258309e-5f


#include "util.inl"

}
}

using namespace bmath;
using namespace bmath::util;


#endif	// _BMATH_MATHUTILITY_H