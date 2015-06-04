/*
	Range utility
	By Dan Buckstein
	Special structure to contain a minimum and maximum value. The structure 
		can denote any type; it will behave the same way for everything.
*/


#ifndef _BMATH_RANGE_H
#define _BMATH_RANGE_H


namespace bmath
{


template <typename type>
struct range
{
	// ctors
	range();
	explicit range(const type minimum, const type maximum);

	// data: minimum and maximum
	type minv;
	type maxv;
};


// operators

// use regular scalar operations to affect the entire range
template <typename type>
const range<type> operator +(const range<type> &r, const float s);
template <typename type>
const range<type> operator +(const float s, const range<type> &r);
template <typename type>
range<type> &operator +=(range<type> &r, const float s);
template <typename type>
const range<type> operator +(const range<type> &r);

template <typename type>
const range<type> operator -(const range<type> &r, const float s);
template <typename type>
const range<type> operator -(const float s, const range<type> &r);
template <typename type>
range<type> &operator -=(range<type> &r, const float s);
template <typename type>
const range<type> operator -(const range<type> &r);

template <typename type>
const range<type> operator *(const range<type> &r, const float s);
template <typename type>
const range<type> operator *(const float s, const range<type> &r);
template <typename type>
range<type> &operator *=(range<type> &r, const float s);

template <typename type>
const range<type> operator /(const range<type> &r, const float s);
template <typename type>
const range<type> operator /(const float s, const range<type> &r);
template <typename type>
range<type> &operator /=(range<type> &r, const float s);



// functions

// swap the values
template <typename type>
const range<type> swapRange(const range<type> &r);

// difference is essentially the span of the range: max - min
template <typename type>
const type diff(const range<type> &r);


#include "range.inl"

}


#endif	// _BMATH_RANGE_H