/*
	mat.inl
	By Dan Buckstein
	Inline function definitions for matrices.
*/


//-----------------------------------------------------------------------------
// mat2

inline mat2::mat2()
{
	// m[column, row]
	m00 = m11 = 1;
	m01 = m10 = 0;
}

inline mat2::mat2(float M00, float M01, 
				  float M10, float M11)
{
	m00 = M00;	m10 = M10;
	m01 = M01;	m11 = M11;
}

inline mat2::mat2(float M)
{
	m00 = m10 = 
	m01 = m11 = M;
}

inline mat2::mat2(const float *Mp)
{
	c0 = (vec2)(Mp);
	c1 = (vec2)(Mp+2);
}

inline mat2::mat2(const vec2 &C0, const vec2 &C1)
{
	c0 = C0;	c1 = C1;
}

inline mat2::mat2(const mat3 &M3)
{
	c0 = M3.c0.xy;	c1 = M3.c1.xy;
}

inline mat2::mat2(const mat4 &M4)
{
	c0 = M4.c0.xy;	c1 = M4.c1.xy;
}


inline mat2 &mat2::set()
{
	// m[column, row]
	m00 = m11 = 1;
	m01 = m10 = 0;
	return *this;
}

inline mat2 &mat2::set(	float M00, float M01, 
						float M10, float M11)
{
	m00 = M00;	m10 = M10;
	m01 = M01;	m11 = M11;
	return *this;
}

inline mat2 &mat2::set(float M)
{
	m00 = m10 = 
	m01 = m11 = M;
	return *this;
}

inline mat2 &mat2::set(const float *Mp)
{
	c0 = (vec2)(Mp);
	c1 = (vec2)(Mp+2);
	return *this;
}

inline mat2 &mat2::set(const vec2 &C0, const vec2 &C1)
{
	c0 = C0;	c1 = C1;
	return *this;
}

inline mat2 &mat2::set(const mat3 &M3)
{
	c0 = M3.c0.xy;	c1 = M3.c1.xy;
	return *this;
}

inline mat2 &mat2::set(const mat4 &M4)
{
	c0 = M4.c0.xy;	c1 = M4.c1.xy;
	return *this;
}


inline const vec2 mat2::operator()(unsigned char r) const
{
	return vec2(*(m+r), *(m+r+2));
}

inline const vec2 mat2::operator[](unsigned char c) const
{
	return *(col+c);
}

inline vec2 &mat2::operator[](unsigned char c)
{
	return *(col+c);
}


inline const vec2 mat2::r0() const
{
	return vec2(*(m  ), *(m+2));
}

inline const vec2 mat2::r1() const
{
	return vec2(*(m+1), *(m+3));
}



//-----------------------------------------------------------------------------
// mat3

inline mat3::mat3()
{
	// m[column, row]
	m00 = m11 = m22 = 1;
	m10 = m20 = m01 = m21 = m02 = m12 = 0;
}

inline mat3::mat3(float M00, float M01, float M02, 
				  float M10, float M11, float M12, 
				  float M20, float M21, float M22 )
{
	m00 = M00;	m10 = M10;	m20 = M20;
	m01 = M01;	m11 = M11;	m21 = M21;
	m02 = M02;	m12 = M12;	m22 = M22;
}

inline mat3::mat3(float M)
{
	m00 = m10 = m20 = 
	m01 = m11 = m21 = 
	m02 = m12 = m22 = M;
}

inline mat3::mat3(const float *Mp)
{
	c0 = (vec3)(Mp);
	c1 = (vec3)(Mp+3);
	c2 = (vec3)(Mp+6);
}

inline mat3::mat3(const vec3 &C0, const vec3 &C1, const vec3 &C2)
{
	c0 = C0;	c1 = C1;	c2 = C2;
}

inline mat3::mat3(const mat2 &M2)
{
	c0 = vec3(M2.c0);	c1 = vec3(M2.c1);	c2 = v3z;
}

inline mat3::mat3(const mat4 &M4)
{
	c0 = M4.c0.xyz;	c1 = M4.c1.xyz;	c2 = M4.c2.xyz;
}


inline mat3 &mat3::set()
{
	// m[column, row]
	m00 = m11 = m22 = 1;
	m10 = m20 = m01 = m21 = m02 = m12 = 0;
	return *this;
}

inline mat3 &mat3::set(float M00, float M01, float M02, 
				  float M10, float M11, float M12, 
				  float M20, float M21, float M22 )
{
	m00 = M00;	m10 = M10;	m20 = M20;
	m01 = M01;	m11 = M11;	m21 = M21;
	m02 = M02;	m12 = M12;	m22 = M22;
	return *this;
}

inline mat3 &mat3::set(float M)
{
	m00 = m10 = m20 = 
	m01 = m11 = m21 = 
	m02 = m12 = m22 = M;
	return *this;
}

inline mat3 &mat3::set(const float *Mp)
{
	c0 = (vec3)(Mp);
	c1 = (vec3)(Mp+3);
	c2 = (vec3)(Mp+6);
	return *this;
}

inline mat3 &mat3::set(const vec3 &C0, const vec3 &C1, const vec3 &C2)
{
	c0 = C0;	c1 = C1;	c2 = C2;
	return *this;
}

inline mat3 &mat3::set(const mat2 &M2)
{
	c0 = vec3(M2.c0);	c1 = vec3(M2.c1);	c2 = v3z;
	return *this;
}

inline mat3 &mat3::set(const mat4 &M4)
{
	c0 = M4.c0.xyz;	c1 = M4.c1.xyz;	c2 = M4.c2.xyz;
	return *this;
}


inline const vec3 mat3::operator()(unsigned char r) const
{
	return vec3(*(m+r), *(m+r+3), *(m+r+6));
}

inline const vec3 mat3::operator[](unsigned char c) const
{
	return *(col+c);
}

inline vec3 &mat3::operator[](unsigned char c)
{
	return *(col+c);
}


inline const vec3 mat3::r0() const
{
	return vec3(*(m  ), *(m+3), *(m+6));
}

inline const vec3 mat3::r1() const
{
	return vec3(*(m+1), *(m+4), *(m+7));
}

inline const vec3 mat3::r2() const
{
	return vec3(*(m+2), *(m+5), *(m+8));
}



//-----------------------------------------------------------------------------
// mat4

inline mat4::mat4()
{
	// m[column, row]
	m00 = m11 = m22 = m33 = 1;
	m10 = m20 = m30 = m01 = m21 = m31 = 
	m02 = m12 = m32 = m03 = m13 = m23 = 0;
}

inline mat4::mat4(float M00, float M01, float M02, float M03, 
				  float M10, float M11, float M12, float M13, 
				  float M20, float M21, float M22, float M23, 
				  float M30, float M31, float M32, float M33 )
{
	m00 = M00;	m10 = M10;	m20 = M20;	m30 = M30;
	m01 = M01;	m11 = M11;	m21 = M21;	m31 = M31;
	m02 = M02;	m12 = M12;	m22 = M22;	m32 = M32;
	m03 = M03;	m13 = M13;	m23 = M23;	m33 = M33;
}

inline mat4::mat4(float M)
{
	m00 = m10 = m20 = m30 = 
	m01 = m11 = m21 = m31 = 
	m02 = m12 = m22 = m32 = 
	m03 = m13 = m23 = m33 = M;
}

inline mat4::mat4(const float *Mp)
{
	c0 = (vec4)(Mp);
	c1 = (vec4)(Mp+4);
	c2 = (vec4)(Mp+8);
	c3 = (vec4)(Mp+12);
}

inline mat4::mat4(const vec4 &C0, const vec4 &C1, const vec4 &C2, const vec4 &C3)
{
	c0 = C0;	c1 = C1;	c2 = C2;	c3 = C3;
}

inline mat4::mat4(const mat2 &M2)
{
	c0 = vec4(M2.c0);	c1 = vec4(M2.c1);	c2 = v4z;		c3 = v4w;
}

inline mat4::mat4(const mat3 &M3)
{
	c0 = vec4(M3.c0);	c1 = vec4(M3.c1);	c2 = vec4(M3.c2);	c3 = v4w;
}


inline mat4 &mat4::set()
{
	// m[column, row]
	m00 = m11 = m22 = m33 = 1;
	m10 = m20 = m30 = m01 = m21 = m31 = 
	m02 = m12 = m32 = m03 = m13 = m23 = 0;
	return *this;
}

inline mat4 &mat4::set(float M00, float M01, float M02, float M03, 
				  float M10, float M11, float M12, float M13, 
				  float M20, float M21, float M22, float M23, 
				  float M30, float M31, float M32, float M33 )
{
	m00 = M00;	m10 = M10;	m20 = M20;	m30 = M30;
	m01 = M01;	m11 = M11;	m21 = M21;	m31 = M31;
	m02 = M02;	m12 = M12;	m22 = M22;	m32 = M32;
	m03 = M03;	m13 = M13;	m23 = M23;	m33 = M33;
	return *this;
}

inline mat4 &mat4::set(float M)
{
	m00 = m10 = m20 = m30 = 
	m01 = m11 = m21 = m31 = 
	m02 = m12 = m22 = m32 = 
	m03 = m13 = m23 = m33 = M;
	return *this;
}

inline mat4 &mat4::set(const float *Mp)
{
	c0 = (vec4)(Mp);
	c1 = (vec4)(Mp+4);
	c2 = (vec4)(Mp+8);
	c3 = (vec4)(Mp+12);
	return *this;
}

inline mat4 &mat4::set(const vec4 &C0, const vec4 &C1, const vec4 &C2, const vec4 &C3)
{
	c0 = C0;	c1 = C1;	c2 = C2;	c3 = C3;
	return *this;
}

inline mat4 &mat4::set(const mat2 &M2)
{
	c0 = vec4(M2.c0);	c1 = vec4(M2.c1);	c2 = v4z;		c3 = v4w;
	return *this;
}

inline mat4 &mat4::set(const mat3 &M3)
{
	c0 = vec4(M3.c0);	c1 = vec4(M3.c1);	c2 = vec4(M3.c2);	c3 = v4w;
	return *this;
}


inline const vec4 mat4::operator()(unsigned char r) const
{
	return vec4(*(m+r), *(m+r+4), *(m+r+8), *(m+r+12));
}

inline const vec4 mat4::operator[](unsigned char c) const
{
	return *(col+c);
}

inline vec4 &mat4::operator[](unsigned char c)
{
	return *(col+c);
}


inline const vec4 mat4::r0() const
{
	return vec4(*(m  ), *(m+4), *(m+8), *(m+12));
}

inline const vec4 mat4::r1() const
{
	return vec4(*(m+1), *(m+5), *(m+9), *(m+13));
}

inline const vec4 mat4::r2() const
{
	return vec4(*(m+2), *(m+6), *(m+10), *(m+14));
}

inline const vec4 mat4::r3() const
{
	return vec4(*(m+3), *(m+7), *(m+11), *(m+15));
}



//-----------------------------------------------------------------------------
// operator definitions

inline const mat2 operator +(const mat2 &m0, const mat2 &m1)
{
	return mat2( m0[0] + m1[0], m0[1] + m1[1] );
}

inline const mat3 operator +(const mat3 &m0, const mat3 &m1)
{
	return mat3( m0[0] + m1[0], m0[1] + m1[1], m0[2] + m1[2] );
}

inline const mat4 operator +(const mat4 &m0, const mat4 &m1)
{
	return mat4( m0[0] + m1[0], m0[1] + m1[1], m0[2] + m1[2], m0[3] + m1[3] );
}


inline mat2 &operator +=(mat2 &m0, const mat2 &m1)
{
	return ( m0 = m0 + m1 );
}

inline mat3 &operator +=(mat3 &m0, const mat3 &m1)
{
	return ( m0 = m0 + m1 );
}

inline mat4 &operator +=(mat4 &m0, const mat4 &m1)
{
	return ( m0 = m0 + m1 );
}


inline const mat2 operator +(const mat2 &m)
{
	return m;
}

inline const mat3 operator +(const mat3 &m)
{
	return m;
}

inline const mat4 operator +(const mat4 &m)
{
	return m;
}


inline const mat2 operator -(const mat2 &m0, const mat2 &m1)
{
	return mat2( m0[0] - m1[0], m0[1] - m1[1] );
}

inline const mat3 operator -(const mat3 &m0, const mat3 &m1)
{
	return mat3( m0[0] - m1[0], m0[1] - m1[1], m0[2] - m1[2] );
}

inline const mat4 operator -(const mat4 &m0, const mat4 &m1)
{
	return mat4( m0[0] - m1[0], m0[1] - m1[1], m0[2] - m1[2], m0[3] - m1[3] );
}


inline mat2 &operator -=(mat2 &m0, const mat2 &m1)
{
	return ( m0 = m0 - m1 );
}

inline mat3 &operator -=(mat3 &m0, const mat3 &m1)
{
	return ( m0 = m0 - m1 );
}

inline mat4 &operator -=(mat4 &m0, const mat4 &m1)
{
	return ( m0 = m0 - m1 );
}


inline const mat2 operator -(const mat2 &m)
{
	return mat2( -m[0], -m[1] );
}

inline const mat3 operator -(const mat3 &m)
{
	return mat3( -m[0], -m[1], -m[2] );
}

inline const mat4 operator -(const mat4 &m)
{
	return mat4( -m[0], -m[1], -m[2], -m[3] );
}


inline const mat2 operator *(const mat2 &m0, const mat2 &m1)
{
	return mat2( m0*m1.c0, m0*m1.c1 );
}

inline const mat3 operator *(const mat3 &m0, const mat3 &m1)
{
	return mat3( m0*m1.c0, m0*m1.c1, m0*m1.c2 );
}

inline const mat4 operator *(const mat4 &m0, const mat4 &m1)
{
	return mat4( m0*m1.c0, m0*m1.c1, m0*m1.c2, m0*m1.c3 );
}


inline mat2 &operator *=(mat2 &m0, const mat2 &m1)
{
	return ( m0 = m0 * m1 );
}

inline mat3 &operator *=(mat3 &m0, const mat3 &m1)
{
	return ( m0 = m0 * m1 );
}

inline mat4 &operator *=(mat4 &m0, const mat4 &m1)
{
	return ( m0 = m0 * m1 );
}


inline const vec2 operator *(const mat2 &m, const vec2 &v)
{
	return vec2( dot(m.r0(),v), dot(m.r1(),v) );
}

inline const vec3 operator *(const mat3 &m, const vec3 &v)
{
	return vec3( dot(m.r0(),v), dot(m.r1(),v), dot(m.r2(),v) );
}

inline const vec4 operator *(const mat4 &m, const vec4 &v)
{
	return vec4( dot(m.r0(),v), dot(m.r1(),v), dot(m.r2(),v), dot(m.r3(),v) );
}


inline vec2 &operator *=(vec2 &v, const mat2 &m)
{
	return ( v = m * v );
}

inline vec3 &operator *=(vec3 &v, const mat3 &m)
{
	return ( v = m * v );
}

inline vec4 &operator *=(vec4 &v, const mat4 &m)
{
	return ( v = m * v );
}


inline const mat2 operator *(const mat2 &m, const float s)
{
	return mat2( m.c0*s, m.c1*s );
}

inline const mat3 operator *(const mat3 &m, const float s)
{
	return mat3( m.c0*s, m.c1*s, m.c2*s );
}

inline const mat4 operator *(const mat4 &m, const float s)
{
	return mat4( m.c0*s, m.c1*s, m.c2*s, m.c3*s );
}


inline const mat2 operator *(const float s, const mat2 &m)
{
	return m*s;
}

inline const mat3 operator *(const float s, const mat3 &m)
{
	return m*s;
}

inline const mat4 operator *(const float s, const mat4 &m)
{
	return m*s;
}


inline mat2 &operator *=(mat2 &m, const float s)
{
	return ( m = m*s );
}

inline mat3 &operator *=(mat3 &m, const float s)
{
	return ( m = m*s );
}

inline mat4 &operator *=(mat4 &m, const float s)
{
	return ( m = m*s );
}


inline const mat2 operator /(const mat2 &m, const float s)
{
	return m*divide(1, s);
}

inline const mat3 operator /(const mat3 &m, const float s)
{
	return m*divide(1, s);
}

inline const mat4 operator /(const mat4 &m, const float s)
{
	return m*divide(1, s);
}


inline const mat2 operator /(const float s, const mat2 &m)
{
	return mat2( s/m.c0, s/m.c1 );
}

inline const mat3 operator /(const float s, const mat3 &m)
{
	return mat3( s/m.c0, s/m.c1, s/m.c2 );
}

inline const mat4 operator /(const float s, const mat4 &m)
{
	return mat4( s/m.c0, s/m.c1, s/m.c2, s/m.c3 );
}


inline mat2 &operator /=(mat2 &m, const float s)
{
	return ( m = m/s );
}

inline mat3 &operator /=(mat3 &m, const float s)
{
	return ( m = m/s );
}

inline mat4 &operator /=(mat4 &m, const float s)
{
	return ( m = m/s );
}


inline bool operator ==(const mat2 &m0, const mat2 &m1)
{
	return memcmp(&m0, &m1, sizeof(m0)) == 0;
}

inline bool operator ==(const mat3 &m0, const mat3 &m1)
{
	return memcmp(&m0, &m1, sizeof(m0)) == 0;
}

inline bool operator ==(const mat4 &m0, const mat4 &m1)
{
	return memcmp(&m0, &m1, sizeof(m0)) == 0;
}


inline bool operator !=(const mat2 &m0, const mat2 &m1)
{
	return !(m0==m1);
}

inline bool operator !=(const mat3 &m0, const mat3 &m1)
{
	return !(m0==m1);
}

inline bool operator !=(const mat4 &m0, const mat4 &m1)
{
	return !(m0==m1);
}



//-----------------------------------------------------------------------------
// special functions

// determinant
inline float determinant(const mat2 &m)
{
	return ( m.m00*m.m11 - m.m10*m.m01 );
}

inline float determinant(const mat3 &m)
{
	return dot(m.c0, cross(m.c1, m.c2));
}


inline float invDeterminant(const mat2 &m)
{
	return divide(1.0f, determinant(m));
}

inline float invDeterminant(const mat3 &m)
{
	return divide(1.0f, determinant(m));
}



// transpose
inline const mat2 transpose(const mat2 &m)
{
	return mat2(m.r0(), m.r1());
}

inline const mat3 transpose(const mat3 &m)
{
	return mat3(m.r0(), m.r1(), m.r2());
}

inline const mat4 transpose(const mat4 &m)
{
	return mat4(m.r0(), m.r1(), m.r2(), m.r3());
}



// axial rotations
inline const mat3 makeRotationX3(float radians)
{
	float c = cosf(radians), s = sinf(radians);
	return mat3( 1,  0,  0, 
				 0,  c,  s, 
				 0, -s,  c );
}

inline const mat4 makeRotationX4(float radians)
{
	float c = cosf(radians), s = sinf(radians);
	return mat4( 1,  0,  0,  0, 
				 0,  c,  s,  0, 
				 0, -s,  c,  0, 
				 0,  0,  0,  1 );
}



inline const mat3 makeRotationY3(float radians)
{
	float c = cosf(radians), s = sinf(radians);
	return mat3( c,  0, -s, 
				 0,  1,  0, 
				 s,  0,  c );
}

inline const mat4 makeRotationY4(float radians)
{
	float c = cosf(radians), s = sinf(radians);
	return mat4( c,  0, -s,  0, 
				 0,  1,  0,  0, 
				 s,  0,  c,  0, 
				 0,  0,  0,  1 );
}



inline const mat2 makeRotationZ2(float radians)
{
	float c = cosf(radians), s = sinf(radians);
	return mat2( c,  s, 
				-s,  c);
}

inline const mat3 makeRotationZ3(float radians)
{
	float c = cosf(radians), s = sinf(radians);
	return mat3( c,  s,  0, 
				-s,  c,  0, 
				 0,  0,  1 );
}

inline const mat4 makeRotationZ4(float radians)
{
	float c = cosf(radians), s = sinf(radians);
	return mat4( c,  s,  0,  0, 
				-s,  c,  0,  0, 
				 0,  0,  1,  0, 
				 0,  0,  0,  1 );
}



// euler angles
inline const mat3 makeRotationEuler3XYZ(float rx, float ry, float rz)
{
	return ( makeRotationX3(rx) * ( makeRotationY3(ry) * makeRotationZ3(rz) ) );
}

inline const mat3 makeRotationEuler3XZY(float rx, float ry, float rz)
{
	return ( makeRotationX3(rx) * ( makeRotationZ3(rz) * makeRotationY3(ry) ) );
}

inline const mat3 makeRotationEuler3YXZ(float rx, float ry, float rz)
{
	return ( makeRotationY3(ry) * ( makeRotationX3(rx) * makeRotationZ3(rz) ) );
}

inline const mat3 makeRotationEuler3YZX(float rx, float ry, float rz)
{
	return ( makeRotationY3(ry) * ( makeRotationZ3(rz) * makeRotationX3(rx) ) );
}

inline const mat3 makeRotationEuler3ZXY(float rx, float ry, float rz)
{
	return ( makeRotationZ3(rz) * ( makeRotationX3(rx) * makeRotationY3(ry) ) );
}

inline const mat3 makeRotationEuler3ZYX(float rx, float ry, float rz)
{
	return ( makeRotationZ3(rz) * ( makeRotationY3(ry) * makeRotationX3(rx) ) );
}


inline const mat4 makeRotationEuler4XYZ(float rx, float ry, float rz)
{
	return makeTransform( makeRotationEuler3XYZ(rx, ry, rz), vec3() );
}

inline const mat4 makeRotationEuler4XZY(float rx, float ry, float rz)
{
	return makeTransform( makeRotationEuler3XZY(rx, ry, rz), vec3() );
}

inline const mat4 makeRotationEuler4YXZ(float rx, float ry, float rz)
{
	return makeTransform( makeRotationEuler3YXZ(rx, ry, rz), vec3() );
}

inline const mat4 makeRotationEuler4YZX(float rx, float ry, float rz)
{
	return makeTransform( makeRotationEuler3YZX(rx, ry, rz), vec3() );
}

inline const mat4 makeRotationEuler4ZXY(float rx, float ry, float rz)
{
	return makeTransform( makeRotationEuler3ZXY(rx, ry, rz), vec3() );
}

inline const mat4 makeRotationEuler4ZYX(float rx, float ry, float rz)
{
	return makeTransform( makeRotationEuler3ZYX(rx, ry, rz), vec3() );
}


// indexed order
inline const mat3 makeRotationEuler3(float rx, float ry, float rz, const unsigned int order[3])
{
	mat3 m[3] = { makeRotationX3(rx), makeRotationY3(ry), makeRotationZ3(rz) };
	return ( m[order[0]] * ( m[order[1]] * m[order[2]] ) );
}

inline const mat3 makeRotationEuler3(float rx, float ry, float rz, const unsigned short order[3])
{
	mat3 m[3] = { makeRotationX3(rx), makeRotationY3(ry), makeRotationZ3(rz) };
	return ( m[order[0]] * ( m[order[1]] * m[order[2]] ) );
}

inline const mat4 makeRotationEuler4(float rx, float ry, float rz, const unsigned int order[3])
{
	return makeTransform( makeRotationEuler3(rx, ry, rz, order), vec3() );
}

inline const mat4 makeRotationEuler4(float rx, float ry, float rz, const unsigned short order[3])
{
	return makeTransform( makeRotationEuler3(rx, ry, rz, order), vec3() );
}



// angle axis
inline const mat3 makeRotationAngleAxis3(float radians, vec3 axis)
{
	float c = cosf(radians), s = sinf(radians);
	float cInv = 1.0f - c;
	axis = normalize(axis);
	return mat3(vec3(c, axis.z*s, -axis.y*s) + (cInv*axis.x)*axis, 
				vec3(-axis.z*s, c, axis.x*s) + (cInv*axis.y)*axis, 
				vec3(axis.y*s, -axis.x*s, c) + (cInv*axis.z)*axis );
}

inline const mat4 makeRotationAngleAxis4(float radians, vec3 axis)
{
	return makeTransform( makeRotationAngleAxis3(radians, axis), vec3() );
}



// scale
inline const mat2 makeScale2(float s)
{
	return mat2( s,  0, 
				 0,  s );
}

inline const mat3 makeScale3(float s)
{
	return mat3( s,  0,  0, 
				 0,  s,  0, 
				 0,  0,  s );
}

inline const mat4 makeScale4(float s)
{
	return mat4( s,  0,  0,  0, 
				 0,  s,  0,  0, 
				 0,  0,  s,  0, 
				 0,  0,  0,  1 );
}


inline const mat2 makeScale2(float sx, float sy)
{
	return mat2(sx,  0, 
				 0, sy );
}

inline const mat3 makeScale3(float sx, float sy, float sz)
{
	return mat3(sx,  0,  0, 
				 0, sy,  0, 
				 0,  0, sz );
}

inline const mat4 makeScale4(float sx, float sy, float sz)
{
	return mat4(sx,  0,  0,  0, 
				 0, sy,  0,  0, 
				 0,  0, sz,  0, 
				 0,  0,  0,  1 );
}



// translation
inline const mat4 makeTranslation4(const vec3 &t)
{
	return mat4(v4x, v4y, v4z, vec4(t, 1));
}

inline const mat4 makeTranslation4(float tx, float ty, float tz)
{
	return mat4(v4x, v4y, v4z, vec4(tx, ty, tz, 1));
}



// homogeneous transform
inline const mat4 makeTransform(const mat3 &r, const vec3 &t)
{
	return mat4( vec4(r.c0), vec4(r.c1), vec4(r.c2), vec4(t, 1) );
}

// rigid body transform with scale
inline const mat4 makeTransform(const mat3 &r, const float s, const vec3 &t)
{
	return makeTransform( r*s, t );
}

inline const mat4 makeTransform(const mat3 &r, const mat3 &s, const vec3 &t)
{
	return makeTransform( r*s, t );
}


inline const mat4 makeRotateScale(const mat3 &r, const float s)
{
	return mat4( vec4(r.c0*s), vec4(r.c1*s), vec4(r.c2*s), v4w );
}

inline const mat4 makeRotateTranslate(const mat3 &r, const vec3 &t)
{
	return mat4( vec4(r.c0), vec4(r.c1), vec4(r.c2), vec4(t, 1) );
}

inline const mat4 makeScaleTranslate(const float s, const vec3 &t)
{
	return mat4( v4x*s, v4y*s, v4z*s, vec4(t, 1) );
}


inline const mat2 inverse(const mat2 &m)
{
	return mat2(m.m11, -m.m01, -m.m10, m.m00) * invDeterminant(m);
}

inline const mat2 inverseNoScale(const mat2 &m)
{
	return transpose(m);
}

inline const mat2 inverseUniformScale(const mat2 &m)
{
	return transpose(m) * invLengthSq(m.c0);
}


inline const mat3 inverse(const mat3 &m)
{
	return mat3(cross(m.c1, m.c2), 
				cross(m.c2, m.c0), 
				cross(m.c0, m.c1)) * invDeterminant(m);
}

inline const mat3 inverseNoScale(const mat3 &m)
{
	return transpose(m);
}

inline const mat3 inverseUniformScale(const mat3 &m)
{
	return transpose(m) * invLengthSq(m.c0);
}


// transform inverse
inline const mat4 transformInverse(const mat4 &m)
{
	// need to extract scale matrix and invert
	// calculation shows that the formula used is correct
	const mat3 rs = transpose(mat3(m.c0.xyz*invLengthSq(m.c0.xyz), 
		m.c1.xyz*invLengthSq(m.c1.xyz), m.c2.xyz*invLengthSq(m.c2.xyz)));
	return makeTransform(rs, -(rs*m.c3.xyz));
}

inline const mat4 transformInverseNoScale(const mat4 &m)
{
	// no scale, assuming magnitude of each column is 1
	const mat3 r = inverseNoScale(mat3(m));
	return makeTransform(r, -(r*m.c3.xyz));
}

inline const mat4 transformInverseUniformScale(const mat4 &m)
{
	// the whole matrix has been scaled, therefore each column has a magnitude of scale
	// to get the inverse rotation matrix, divide by scale twice, or s^2
	const mat3 rs = inverseUniformScale(mat3(m));
	return makeTransform(rs, -(rs*m.c3.xyz));
}


inline const vec3 multMat4Vec3(const mat4 &m, const vec3 &v)
{
	return vec3(dot(m.r0().xyz, v) + m.c3.x, 
				dot(m.r1().xyz, v) + m.c3.y, 
				dot(m.r2().xyz, v) + m.c3.z );
}

inline const vec3 multMat4Vec3NoTranslate(const mat4 &m, const vec3 &v)
{
	return vec3(dot(m.r0().xyz, v), 
				dot(m.r1().xyz, v), 
				dot(m.r2().xyz, v) );
}



// projections
inline const mat4 makePerspective(float fovyRadians, float aspectRatio, 
	float znear, float zfar)
{
	mat4 ret;

	// validate parameters
	if ((fovyRadians > 0.0f) && (fovyRadians < (float)M_PI) && 
		(aspectRatio > 0.0f) && 
		(znear > 0.0f) && (zfar > znear))
	{
		const float top = znear * tanf(fovyRadians*0.5f);
		const float right = aspectRatio * top;

		ret.m00 =  znear / (right);
		ret.m11 =  znear / (top);
		ret.m22 = -(zfar + znear) / (zfar - znear);
		ret.m32 = -2.0f*znear*zfar/ (zfar - znear);
		ret.m23 = -1.0f;
		ret.m33 = 0.0f;
	}
	return ret;
}

inline const mat4 makePerspective(float left, float right, float bottom, float top, 
	float znear, float zfar)
{
	mat4 ret;

	if ((right - left > 0.0f) && (top - bottom > 0.0f) && 
		(znear > 0.0f) && (zfar > znear))
	{
		ret.m00 =  2.0f*znear / (right - left);
		ret.m11 =  2.0f*znear / (top - bottom);
		ret.m20 =  (right + left) / (right - left);
		ret.m21 =  (top + bottom) / (top - bottom);
		ret.m22 = -(zfar + znear) / (zfar - znear);
		ret.m32 = -2.0f*znear*zfar/ (zfar - znear);
		ret.m23 = -1.0f;
		ret.m33 = 0.0f;
	}
	return ret;
}

inline const mat4 makeOrthographic(float width, float height, 
	float znear, float zfar)
{
	mat4 ret;

	if ((width != 0.0f) && (height != 0.0f) && 
		(znear - zfar != 0.0f))
	{
		ret.m00 =  2.0f*znear / (width);
		ret.m11 =  2.0f*znear / (height);
		ret.m22 = -2.0f / (zfar - znear);
		ret.m32 = -(zfar + znear) / (zfar - znear);
	}
	return ret;
}

inline const mat4 makeOrthographic(float left, float right, float bottom, float top, 
	float znear, float zfar)
{
	mat4 ret;

	if ((right - left != 0.0f) && (top - bottom != 0.0f) && 
		(znear - zfar != 0.0f))
	{
		ret.m00 =  2.0f*znear / (right - left);
		ret.m11 =  2.0f*znear / (top - bottom);
		ret.m22 = -2.0f / (zfar - znear);
		ret.m30 = -(right + left) / (right - left);
		ret.m31 = -(top + bottom) / (top - bottom);
		ret.m32 = -(zfar + znear) / (zfar - znear);
	}
	return ret;
}
