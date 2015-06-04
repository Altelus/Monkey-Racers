/*
	Math Utility.inl
	By Dan Buckstein
	Inline definitions for math utilities.
*/


//-----------------------------------------------------------------------------
// methods

// random number generators

inline float random(const float vMin, const float vMax)
{
	return ( (float)rand()*invRandMaxf*(vMax - vMin) + vMin );
}

inline float randomNorm()
{
	return ( (float)rand()*invRandMaxf );
}

inline float randomSymm()
{
	return ( (float)rand()*invRandMaxf*2.0f - 1.0f );
}



//-----------------------------------------------------------------------------
// stats

inline unsigned int summation(unsigned int n)
{
	return ( n*(n+1)/2 );
}

inline float summationf(unsigned int n)
{
	return (float)summation(n);
}


inline unsigned int factorial(unsigned int n)
{
	unsigned int f = 1;
	for ( ; n > 1; f *= (n--) );
	return f;
}

inline float factorialf(unsigned int n)
{
	return (float)factorial(n);
}


inline unsigned int permutation(unsigned int n, unsigned int k)
{
	if (k <= n)
		return ( factorial(n) / factorial(n-k) );
	return 0;
}

inline float permutationf(unsigned int n, unsigned int k)
{
	return (float)permutation(n, k);
}


inline unsigned int combination(unsigned int n, unsigned int k)
{
	if (k <= n)
		return ( factorial(n) / ( factorial(k)*factorial(n-k) ) );
	return 0;
}

inline float combinationf(unsigned int n, unsigned int k)
{
	return (float)combination(n, k);
}



//-----------------------------------------------------------------------------
//operations

inline float easeInParam(float t)
{
	t = t - 1.0f;
	return (1.0f - (t*t));
}

inline float easeOutParam(float t)
{
	return (t*t);
}


inline float divide(const float numerator, const float denominator)
{
	return ( (denominator) ? (numerator/denominator) : (0) );
}


inline float absVal(const float n)
{
	return ( (n >= 0.0f) ? (n) : (-n) );
}

inline float sign(const float n)
{
	return ( (n != 0.0f) ? ( (n > 0.0f) ? (1.0f) : (-1.0f) ) : 0.0f );
}

inline float dot(const float n0, const float n1)
{
	return (n0*n1);
}

inline float length(const float n)
{
	return absVal(n);
}

inline float normalize(const float n)
{
	return sign(n);
}


template <typename type>
inline float length(const type n)
{
	return sqrtf(lengthSq(n));
}

template <typename type>
inline float lengthSq(const type n)
{
	return dot(n, n);
}

template <typename type>
inline float invLength(const type n)
{
	return divide(1.0f, length(n));
}

template <typename type>
inline float invLengthSq(const type n)
{
	return divide(1.0f, lengthSq(n));
}

template <typename type>
inline type normalize(const type n)
{
	return ( n*invLength(n) );
}

template <typename type>
inline float projScalar(const type n, const type onto)
{
	return divide(dot(n, onto), lengthSq(onto));
}

template <typename type>
inline type proj(const type n, const type onto)
{
	return ( onto*projScalar(n, onto) );
}


template <typename type>
inline type recip(const type n)
{
	return ( 1.0f / n );
}


template <typename type>
inline type clamp(const type value, const type minimum, const type maximum)
{
	return ( value - minimum < 0 ? minimum : ( value - maximum > 0 ? maximum : value ) );
}


// LERP
template <typename type>
inline type lerp(const type n0, const type n1, const float t)
{
#ifdef	_BMATH_LERP_ALT
	// p = p0 + (p1 - p0)t
	return ( n0 + (n1 - n0)*t );
#else
	// p = p0(1-t) + p1(t)
	return ( n0*(1.0f-t) + n1*(t) );
#endif	// _BMATH_LERP_ALT
}


template <typename type>
inline float invLerp(const type n0, const type n1, const type value)
{
	// t = (p - p0) / (p1 - p0)
	// mathematically works out to the projection of the difference from 
	//	p0 to the result, onto p0 to p1
	return projScalar((value-p0), (p1-p0));
}

template <typename type>
inline void invLerp(const type n0, const type n1, const type value, float &t)
{
	t = invLerp(n0, n1, value);
}
