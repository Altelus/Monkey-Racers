/*
	range.inl
	Inline function definitions for range structure.
*/


// ctor
template <typename type>
inline range<type>::range()
	: minv(0), maxv(0)
{
	// do nothing
}

template <typename type>
inline range<type>::range(const type minimum, const type maximum)
	: minv(minimum), maxv(maximum)
{
	// do nothing
}



//-----------------------------------------------------------------------------
// operators

template <typename type>
inline const range<type> operator +(const range<type> &r, const float s)
{
	return range<type>(r.minv + s, r.maxv + s);
}

template <typename type>
inline const range<type> operator +(const float s, const range<type> &r)
{
	return r + s;
}

template <typename type>
inline range<type> &operator +=(range<type> &r, const float s)
{
	return ( r = r + s );
}

template <typename type>
inline const range<type> operator +(const range<type> &r)
{
	return r;
}


template <typename type>
inline const range<type> operator -(const range<type> &r, const float s)
{
	return range<type>(r.minv - s, r.maxv - s);
}

template <typename type>
inline const range<type> operator -(const float s, const range<type> &r)
{
	return (-r) + s;
}

template <typename type>
inline range<type> &operator -=(range<type> &r, const float s)
{
	return ( r = r - s );
}

template <typename type>
inline const range<type> operator -(const range<type> &r)
{
	return range<type>(-r.minv, -r.maxv);
}


template <typename type>
inline const range<type> operator *(const range<type> &r, const float s)
{
	return range<type>(r.minv*s, r.maxv*s);
}

template <typename type>
inline const range<type> operator *(const float s, const range<type> &r)
{
	return r*s;
}

template <typename type>
inline range<type> &operator *=(range<type> &r, const float s)
{
	return ( r = r*s );
}


template <typename type>
inline const range<type> operator /(const range<type> &r, const float s)
{
	return range<type>(r.minv/s, r.maxv/s);
}

template <typename type>
inline const range<type> operator /(const float s, const range<type> &r)
{
	return range<type>(s/r.minv, s/r.maxv);
}

template <typename type>
inline range<type> &operator /=(range<type> &r, const float s)
{
	return ( r = r/s );
}



//-----------------------------------------------------------------------------
// functions

template <typename type>
inline const range<type> swapRange(const range<type> &r)
{
	return range<type>(r.maxv, r.minv);
}

template <typename type>
inline const type diff(const range<type> &r)
{
	return ( r.maxv - r.minv );
}
