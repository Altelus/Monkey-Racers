/*
	vec.inl
	By Dan Buckstein
	Inline function definitions for vectors.
*/


//-----------------------------------------------------------------------------
// vec2

inline vec2::vec2()
{
	x = y = 0;
}

inline vec2::vec2(float X, float Y)
{
	x = X;		y = Y;
}

inline vec2::vec2(float V)
{
	x = y = V;
}

inline vec2::vec2(const float *Vp)
{
	x =*(Vp);	y =*(Vp+1);
}

inline vec2::vec2(const vec3 &v3)
{
	x = v3.x;	y = v3.y;
}

inline vec2::vec2(const vec4 &v4)
{
	x = v4.x;	y = v4.y;
}


inline vec2 &vec2::set()
{
	x = y = 0;
	return *this;
}

inline vec2 &vec2::set(float X, float Y)
{
	x = X;		y = Y;
	return *this;
}

inline vec2 &vec2::set(float V)
{
	x = y = V;
	return *this;
}

inline vec2 &vec2::set(const float *Vp)
{
	x =*(Vp);	y =*(Vp+1);
	return *this;
}

inline vec2 &vec2::set(const vec3 &v3)
{
	x = v3.x;	y = v3.y;
	return *this;
}

inline vec2 &vec2::set(const vec4 &v4)
{
	x = v4.x;	y = v4.y;
	return *this;
}


inline const float vec2::operator[](unsigned char r) const
{
	return *(v+r);
}

inline float &vec2::operator[](unsigned char r)
{
	return *(v+r);
}



//-----------------------------------------------------------------------------
// vec3

inline vec3::vec3()
{
	x = y = z = 0;
}

inline vec3::vec3(float X, float Y, float Z)
{
	x = X;		y = Y;		z = Z;
}

inline vec3::vec3(float V)
{
	x = y = z = V;
}

inline vec3::vec3(const float *Vp)
{
	x =*(Vp);	y =*(Vp+1);	z =*(Vp+2);
}

inline vec3::vec3(const vec2 &v2, float Z)
{
	x = v2.x;	y = v2.y;	z = Z;
}

inline vec3::vec3(const vec4 &v4)
{
	x = v4.x;	y = v4.y;	z = v4.z;
}


inline vec3 &vec3::set()
{
	x = y = z = 0;
	return *this;
}

inline vec3 &vec3::set(float X, float Y, float Z)
{
	x = X;		y = Y;		z = Z;
	return *this;
}

inline vec3 &vec3::set(float V)
{
	x = y = z = V;
	return *this;
}

inline vec3 &vec3::set(const float *Vp)
{
	x =*(Vp);	y =*(Vp+1);	z =*(Vp+2);
	return *this;
}

inline vec3 &vec3::set(const vec2 &v2, float Z)
{
	x = v2.x;	y = v2.y;	z = Z;
	return *this;
}

inline vec3 &vec3::set(const vec4 &v4)
{
	x = v4.x;	y = v4.y;	z = v4.z;
	return *this;
}


inline const float vec3::operator[](unsigned char r) const
{
	return *(v+r);
}

inline float &vec3::operator[](unsigned char r)
{
	return *(v+r);
}



//-----------------------------------------------------------------------------
// vec4

inline vec4::vec4()
{
	x = y = z = w = 0;
}

inline vec4::vec4(float X, float Y, float Z, float W)
{
	x = X;		y = Y;		z = Z;		w = W;
}

inline vec4::vec4(float V)
{
	x = y = z = w = V;
}

inline vec4::vec4(const float *Vp)
{
	x =*(Vp);	y =*(Vp+1);	z =*(Vp+2);	w =*(Vp+3);
}

inline vec4::vec4(const vec2 &v2, float Z, float W)
{
	x = v2.x;	y = v2.y;	z = Z;		w = W;
}

inline vec4::vec4(const vec3 &v3, float W)
{
	x = v3.x;	y = v3.y;	z = v3.z;	w = W;
}


inline vec4 &vec4::set()
{
	x = y = z = w = 0;
	return *this;
}

inline vec4 &vec4::set(float X, float Y, float Z, float W)
{
	x = X;		y = Y;		z = Z;		w = W;
	return *this;
}

inline vec4 &vec4::set(float V)
{
	x = y = z = w = V;
	return *this;
}

inline vec4 &vec4::set(const float *Vp)
{
	x =*(Vp);	y =*(Vp+1);	z =*(Vp+2);	w =*(Vp+3);
	return *this;
}

inline vec4 &vec4::set(const vec2 &v2, float Z, float W)
{
	x = v2.x;	y = v2.y;	z = Z;		w = W;
	return *this;
}

inline vec4 &vec4::set(const vec3 &v3, float W)
{
	x = v3.x;	y = v3.y;	z = v3.z;	w = W;
	return *this;
}


inline const float vec4::operator[](unsigned char r) const
{
	return *(v+r);
}

inline float &vec4::operator[](unsigned char r)
{
	return *(v+r);
}



//-----------------------------------------------------------------------------
// operator definitions

inline float dot(const vec2 &v0, const vec2 &v1)
{
	return ( v0.x*v1.x + v0.y*v1.y );
}

inline float dot(const vec3 &v0, const vec3 &v1)
{
	return ( v0.x*v1.x + v0.y*v1.y + v0.z*v1.z );
}

inline float dot(const vec4 &v0, const vec4 &v1)
{
	return ( v0.x*v1.x + v0.y*v1.y + v0.z*v1.z + v0.w*v1.w );
}


inline const vec2 operator +(const vec2 &v0, const vec2 &v1)
{
	return vec2( v0.x + v1.x, v0.y + v1.y );
}

inline const vec3 operator +(const vec3 &v0, const vec3 &v1)
{
	return vec3( v0.x + v1.x, v0.y + v1.y, v0.z + v1.z );
}

inline const vec4 operator +(const vec4 &v0, const vec4 &v1)
{
	return vec4( v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w );
}


inline vec2 &operator +=(vec2 &v0, const vec2 &v1)
{
	return ( v0 = v0 + v1 );
}

inline vec3 &operator +=(vec3 &v0, const vec3 &v1)
{
	return ( v0 = v0 + v1 );
}

inline vec4 &operator +=(vec4 &v0, const vec4 &v1)
{
	return ( v0 = v0 + v1 );
}


inline const vec2 operator +(const vec2 &v)
{
	return v;
}

inline const vec3 operator +(const vec3 &v)
{
	return v;
}

inline const vec4 operator +(const vec4 &v)
{
	return v;
}


inline const vec2 operator -(const vec2 &v0, const vec2 &v1)
{
	return vec2( v0.x - v1.x, v0.y - v1.y );
}

inline const vec3 operator -(const vec3 &v0, const vec3 &v1)
{
	return vec3( v0.x - v1.x, v0.y - v1.y, v0.z - v1.z );
}

inline const vec4 operator -(const vec4 &v0, const vec4 &v1)
{
	return vec4( v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w );
}


inline vec2 &operator -=(vec2 &v0, const vec2 &v1)
{
	return ( v0 = v0 - v1 );
}

inline vec3 &operator -=(vec3 &v0, const vec3 &v1)
{
	return ( v0 = v0 - v1 );
}

inline vec4 &operator -=(vec4 &v0, const vec4 &v1)
{
	return ( v0 = v0 - v1 );
}


inline const vec2 operator -(const vec2 &v)
{
	return vec2( -v.x, -v.y );
}

inline const vec3 operator -(const vec3 &v)
{
	return vec3( -v.x, -v.y, -v.z );
}

inline const vec4 operator -(const vec4 &v)
{
	return vec4( -v.x, -v.y, -v.z, -v.w );
}


inline const vec2 operator *(const vec2 &v, const float s)
{
	return vec2( v.x*s, v.y*s );
}

inline const vec3 operator *(const vec3 &v, const float s)
{
	return vec3( v.x*s, v.y*s, v.z*s );
}

inline const vec4 operator *(const vec4 &v, const float s)
{
	return vec4( v.x*s, v.y*s, v.z*s, v.w*s );
}


inline const vec2 operator *(const float s, const vec2 &v)
{
	return v*s;
}

inline const vec3 operator *(const float s, const vec3 &v)
{
	return v*s;
}

inline const vec4 operator *(const float s, const vec4 &v)
{
	return v*s;
}


inline vec2 &operator *=(vec2 &v, const float s)
{
	return ( v = v*s );
}

inline vec3 &operator *=(vec3 &v, const float s)
{
	return ( v = v*s );
}

inline vec4 &operator *=(vec4 &v, const float s)
{
	return ( v = v*s );
}


inline const vec2 operator /(const vec2 &v, const float s)
{
	return v*divide(1, s);
}

inline const vec3 operator /(const vec3 &v, const float s)
{
	return v*divide(1, s);
}

inline const vec4 operator /(const vec4 &v, const float s)
{
	return v*divide(1, s);
}


inline const vec2 operator /(const float s, const vec2 &v)
{
	return vec2( divide(s, v.x), divide(s, v.y) );
}

inline const vec3 operator /(const float s, const vec3 &v)
{
	return vec3( divide(s, v.x), divide(s, v.y), divide(s, v.z) );
}

inline const vec4 operator /(const float s, const vec4 &v)
{
	return vec4( divide(s, v.x), divide(s, v.y), divide(s, v.z), divide(s, v.w) );
}


inline vec2 &operator /=(vec2 &v, const float s)
{
	return ( v = v/s );
}

inline vec3 &operator /=(vec3 &v, const float s)
{
	return ( v = v/s );
}

inline vec4 &operator /=(vec4 &v, const float s)
{
	return ( v = v/s );
}


inline bool operator ==(const vec2 &v0, const vec2 &v1)
{
	return memcmp(&v0, &v1, sizeof(v0)) == 0;
}

inline bool operator ==(const vec3 &v0, const vec3 &v1)
{
	return memcmp(&v0, &v1, sizeof(v0)) == 0;
}

inline bool operator ==(const vec4 &v0, const vec4 &v1)
{
	return memcmp(&v0, &v1, sizeof(v0)) == 0;
}


inline bool operator !=(const vec2 &v0, const vec2 &v1)
{
	return !(v0==v1);
}

inline bool operator !=(const vec3 &v0, const vec3 &v1)
{
	return !(v0==v1);
}

inline bool operator !=(const vec4 &v0, const vec4 &v1)
{
	return !(v0==v1);
}



//-----------------------------------------------------------------------------
// special operators

// component-wise multiplication
inline const vec2 operator *(const vec2 &v0, const vec2 &v1)
{
	return vec2( v0.x*v1.x, v0.y*v1.y );
}

inline const vec3 operator *(const vec3 &v0, const vec3 &v1)
{
	return vec3( v0.x*v1.x, v0.y*v1.y, v0.z*v1.z );
}

inline const vec4 operator *(const vec4 &v0, const vec4 &v1)
{
	return vec4( v0.x*v1.x, v0.y*v1.y, v0.z*v1.z, v0.w*v1.w );
}


inline vec2 &operator *=(vec2 &v0, const vec2 &v1)
{
	return ( v0 = v0*v1 );
}

inline vec3 &operator *=(vec3 &v0, const vec3 &v1)
{
	return ( v0 = v0*v1 );
}

inline vec4 &operator *=(vec4 &v0, const vec4 &v1)
{
	return ( v0 = v0*v1 );
}


inline const vec2 operator /(const vec2 &v0, const vec2 &v1)
{
	return vec2( divide(v0.x, v1.x), divide(v0.y, v1.y) );
}

inline const vec3 operator /(const vec3 &v0, const vec3 &v1)
{
	return vec3( divide(v0.x, v1.x), divide(v0.y, v1.y), divide(v0.z, v1.z) );
}

inline const vec4 operator /(const vec4 &v0, const vec4 &v1)
{
	return vec4( divide(v0.x, v1.x), divide(v0.y, v1.y), divide(v0.z, v1.z), divide(v0.w, v1.w) );
}


inline vec2 &operator /=(vec2 &v0, const vec2 &v1)
{
	return ( v0 = v0/v1 );
}

inline vec3 &operator /=(vec3 &v0, const vec3 &v1)
{
	return ( v0 = v0/v1 );
}

inline vec4 &operator /=(vec4 &v0, const vec4 &v1)
{
	return ( v0 = v0/v1 );
}



// addition with scalars
inline const vec2 operator +(const vec2 &v, const float s)
{
	return vec2( v.x+s, v.y+s );
}

inline const vec3 operator +(const vec3 &v, const float s)
{
	return vec3( v.x+s, v.y+s, v.z+s );
}

inline const vec4 operator +(const vec4 &v, const float s)
{
	return vec4( v.x+s, v.y+s, v.z+s, v.w+s );
}


inline const vec2 operator +(const float s, const vec2 &v)
{
	return v+s;
}

inline const vec3 operator +(const float s, const vec3 &v)
{
	return v+s;
}

inline const vec4 operator +(const float s, const vec4 &v)
{
	return v+s;
}


inline vec2 &operator +=(vec2 &v, const float s)
{
	return ( v = v+s );
}

inline vec3 &operator +=(vec3 &v, const float s)
{
	return ( v = v+s );
}

inline vec4 &operator +=(vec4 &v, const float s)
{
	return ( v = v+s );
}


inline const vec2 operator -(const vec2 &v, const float s)
{
	return vec2( v.x-s, v.y-s );
}

inline const vec3 operator -(const vec3 &v, const float s)
{
	return vec3( v.x-s, v.y-s, v.z-s );
}

inline const vec4 operator -(const vec4 &v, const float s)
{
	return vec4( v.x-s, v.y-s, v.z-s, v.w-s );
}


inline const vec2 operator -(const float s, const vec2 &v)
{
	return ( (-v)+s );
}

inline const vec3 operator -(const float s, const vec3 &v)
{
	return ( (-v)+s );
}

inline const vec4 operator -(const float s, const vec4 &v)
{
	return ( (-v)+s );
}


inline vec2 &operator -=(vec2 &v, const float s)
{
	return ( v = v-s );
}

inline vec3 &operator -=(vec3 &v, const float s)
{
	return ( v = v-s );
}

inline vec4 &operator -=(vec4 &v, const float s)
{
	return ( v = v-s );
}



//-----------------------------------------------------------------------------
// special functions

// quick rotation for vec2
inline const vec2 rotate(const float angle, const vec2 &v)
{
	return rotate(cosf(angle), sinf(angle), v);
}

inline const vec2 rotate(const float cosine, const float sine, const vec2 &v)
{
	return vec2((cosine*v.x - sine*v.y), (sine*v.x + cosine*v.y));
}


// cross product for vec3 only
inline const vec3 cross(const vec3 &v0, const vec3 &v1)
{
	return vec3(v0.y*v1.z-v0.z*v1.y, 
				v0.z*v1.x-v0.x*v1.z, 
				v0.x*v1.y-v0.y*v1.x);
}

inline const vec3 crossNormalize(const vec3 &v0, const vec3 &v1)
{
	return normalize(cross(v0, v1));
}


// normal calculation
inline const vec3 computeTriNormal(const vec3 &v0, const vec3 &v1, const vec3 &v2)
{
	return crossNormalize( v1-v0, v2-v0 );
}


// area calculation
inline float computeTriArea(const vec3 &v0, const vec3 &v1, const vec3 &v2)
{
	return length(cross( v1-v0, v2-v0));
}


// area and normal
inline float computeTriAreaNormal(const vec3 &v0, const vec3 &v1, const vec3 &v2, vec3 &normal)
{
	normal = cross( v1-v0, v2-v0 );
	float ret = length(normal);
	normal = normal / ret;
	return ret;
}


// Gram-Schmidt orthogonalization process
// ****does not normalize!
inline void GramSchmidt(const vec2 &base, vec2 &v)
{
	v = v - proj(v, base);
}

inline void GramSchmidt(const vec3 &base, vec3 &v)
{
	v = v - proj(v, base);
}

inline void GramSchmidt(const vec3 &base, vec3 &v0, vec3 &v1)
{
	v0 = v0 - proj(v0, base);
	v1 = v1 - proj(v1, base) - proj(v1, v0);
}



inline float edgeToPointRadius(double separationRadians)
{
	// originally computing the magnitude of the point linearly interpolated 
	//	between (1, 0) and v(theta), but thanks to trigonometric identities, 
	//	that simplifies down to this
	return (float)cos(0.5*separationRadians);
}

inline float pointToEdgeRadius(double separationRadians)
{
	return divide(1.0f, (float)cos(0.5*separationRadians));
}

inline float edgeToPointRadius(double separationRadians, float scalar)
{
	return scalar*(float)cos(0.5*separationRadians);
}

inline float pointToEdgeRadius(double separationRadians, float scalar)
{
	return divide(scalar, (float)cos(0.5*separationRadians));
}


inline float faceToPointRadius(double sepAzimuth, double sepElevation)
{
	// this is pretty much the same as the above but this time it is done on two axes
	// the result is as if we have computed the magitude of the edge alone, rotated 
	//	the model and computed the magnitude of the rotated slice; i.e. cos * cos
	return (float)(cos(0.5*sepAzimuth)*cos(0.5*sepElevation));
}

inline float pointToFaceRadius(double sepAzimuth, double sepElevation)
{
	return divide(1.0f, (float)(cos(0.5*sepAzimuth)*cos(0.5*sepElevation)));
}

inline float faceToPointRadius(double sepAzimuth, double sepElevation, float scalar)
{
	return scalar*(float)(cos(0.5*sepAzimuth)*cos(0.5*sepElevation));
}

inline float pointToFaceRadius(double sepAzimuth, double sepElevation, float scalar)
{
	return divide(scalar, (float)(cos(0.5*sepAzimuth)*cos(0.5*sepElevation)));
}
