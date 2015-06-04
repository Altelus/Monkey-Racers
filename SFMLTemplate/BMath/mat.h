/*
	Matrix classes
	By Dan Buckstein
	Standalone matrix classes.
	Contains structures for 2D, 3D and 4D *column-major matrices, with associated 
		functions and operators.
	The primary purpose for these structures is for rigid transforms, not just 
		any old matrix, but feel free to extend these if you wish!

	*Column-major: this is how the data in the array is arranged in matrix form:
		0	4	8	12
		1	5	9	13
		2	6	10	14
		3	7	11	15
*/


#ifndef _BMATH_MAT_H
#define _BMATH_MAT_H


#include "BMath/vec.h"
// these structures describe column-major matrices
// they are arranged here as the transpose of the actual data
// the first number refers to the column
//	m.m[column, row]


namespace bmath
{
namespace mat
{


union mat2;
union mat3;
union mat4;


//-----------------------------------------------------------------------------
// structures

union mat2
{
	// ctor (default is identity)
	mat2();
	explicit mat2(	float M00, float M01, 
					float M10, float M11);
	explicit mat2(float M);
	explicit mat2(const float *Mp);
	explicit mat2(const vec2 &C0, const vec2 &C1);
	explicit mat2(const mat3 &M3);
	explicit mat2(const mat4 &M4);

	// set and reset
	mat2 &set();
	mat2 &set(	float M00, float M01, 
				float M10, float M11);
	mat2 &set(float M);
	mat2 &set(const float *Mp);
	mat2 &set(const vec2 &C0, const vec2 &C1);
	mat2 &set(const mat3 &M3);
	mat2 &set(const mat4 &M4);
	
	// access values as (row) or [column]
	const vec2 operator()(unsigned char r) const;
	const vec2 operator[](unsigned char c) const;
	vec2 &operator[](unsigned char c);

	// get row
	const vec2 r0() const;
	const vec2 r1() const;

	// data
	struct { vec2 c0, c1; };
	struct { vec2 col[2]; };
	struct { float 
		m00, m01, 
		m10, m11; };
	float mm[2][2];
	float m[4];
};
static const mat2 m2Identity;


union mat3
{
	// ctor (default is identity)
	mat3();
	explicit mat3(	float M00, float M01, float M02, 
					float M10, float M11, float M12, 
					float M20, float M21, float M22 );
	explicit mat3(float M);
	explicit mat3(const float *Mp);
	explicit mat3(const vec3 &C0, const vec3 &C1, const vec3 &C2);
	explicit mat3(const mat2 &M2);
	explicit mat3(const mat4 &M4);
	
	// set and reset
	mat3 &set();
	mat3 &set(	float M00, float M01, float M02, 
				float M10, float M11, float M12, 
				float M20, float M21, float M22 );
	mat3 &set(float M);
	mat3 &set(const float *Mp);
	mat3 &set(const vec3 &C0, const vec3 &C1, const vec3 &C2);
	mat3 &set(const mat2 &M2);
	mat3 &set(const mat4 &M4);
	
	// access values as (row) or [column]
	const vec3 operator()(unsigned char r) const;
	const vec3 operator[](unsigned char c) const;
	vec3 &operator[](unsigned char c);

	// get row
	const vec3 r0() const;
	const vec3 r1() const;
	const vec3 r2() const;

	// data
	struct { vec3 c0, c1, c2; };
	struct { vec3 col[3]; };
	struct { float 
		m00, m01, m02, 
		m10, m11, m12, 
		m20, m21, m22; };
	float mm[3][3];
	float m[9];
};
static const mat3 m3Identity;


union mat4
{
	// ctor (default is identity)
	mat4();
	explicit mat4(	float M00, float M01, float M02, float M03, 
					float M10, float M11, float M12, float M13, 
					float M20, float M21, float M22, float M23, 
					float M30, float M31, float M32, float M33 );
	explicit mat4(float M);
	explicit mat4(const float *Mp);
	explicit mat4(const vec4 &C0, const vec4 &C1, const vec4 &C2, const vec4 &C3);
	explicit mat4(const mat2 &M2);
	explicit mat4(const mat3 &M3);
	
	// set and reset
	mat4 &set();
	mat4 &set(	float M00, float M01, float M02, float M03, 
				float M10, float M11, float M12, float M13, 
				float M20, float M21, float M22, float M23, 
				float M30, float M31, float M32, float M33 );
	mat4 &set(float M);
	mat4 &set(const float *Mp);
	mat4 &set(const vec4 &C0, const vec4 &C1, const vec4 &C2, const vec4 &C3);
	mat4 &set(const mat2 &M2);
	mat4 &set(const mat3 &M3);
	
	// access values as (row) or [column]
	const vec4 operator()(unsigned char r) const;
	const vec4 operator[](unsigned char c) const;
	vec4 &operator[](unsigned char c);

	// get row
	const vec4 r0() const;
	const vec4 r1() const;
	const vec4 r2() const;
	const vec4 r3() const;

	// data
	struct { vec4 c0, c1, c2, c3; };
	struct { vec4 col[4]; };
	struct { float 
		m00, m01, m02, m03, 
		m10, m11, m12, m13, 
		m20, m21, m22, m23, 
		m30, m31, m32, m33; };
	float mm[4][4];
	float m[16];
};
static const mat4 m4Identity;



//-----------------------------------------------------------------------------
// operators

const mat2 operator +(const mat2 &m0, const mat2 &m1);
const mat3 operator +(const mat3 &m0, const mat3 &m1);
const mat4 operator +(const mat4 &m0, const mat4 &m1);

mat2 &operator +=(mat2 &m0, const mat2 &m1);
mat3 &operator +=(mat3 &m0, const mat3 &m1);
mat4 &operator +=(mat4 &m0, const mat4 &m1);

const mat2 operator +(const mat2 &m);
const mat3 operator +(const mat3 &m);
const mat4 operator +(const mat4 &m);

const mat2 operator -(const mat2 &m0, const mat2 &m1);
const mat3 operator -(const mat3 &m0, const mat3 &m1);
const mat4 operator -(const mat4 &m0, const mat4 &m1);

mat2 &operator -=(mat2 &m0, const mat2 &m1);
mat3 &operator -=(mat3 &m0, const mat3 &m1);
mat4 &operator -=(mat4 &m0, const mat4 &m1);

const mat2 operator -(const mat2 &m);
const mat3 operator -(const mat3 &m);
const mat4 operator -(const mat4 &m);

const mat2 operator *(const mat2 &m0, const mat2 &m1);
const mat3 operator *(const mat3 &m0, const mat3 &m1);
const mat4 operator *(const mat4 &m0, const mat4 &m1);

mat2 &operator *=(mat2 &m0, const mat2 &m1);
mat3 &operator *=(mat3 &m0, const mat3 &m1);
mat4 &operator *=(mat4 &m0, const mat4 &m1);

const vec2 operator *(const mat2 &m, const vec2 &v);
const vec3 operator *(const mat3 &m, const vec3 &v);
const vec4 operator *(const mat4 &m, const vec4 &v);

vec2 &operator *=(vec2 &v, const mat2 &m);
vec3 &operator *=(vec3 &v, const mat3 &m);
vec4 &operator *=(vec4 &v, const mat4 &m);

const mat2 operator *(const mat2 &m, const float s);
const mat3 operator *(const mat3 &m, const float s);
const mat4 operator *(const mat4 &m, const float s);

const mat2 operator *(const float s, const mat2 &m);
const mat3 operator *(const float s, const mat3 &m);
const mat4 operator *(const float s, const mat4 &m);

mat2 &operator *=(mat2 &m, const float s);
mat3 &operator *=(mat3 &m, const float s);
mat4 &operator *=(mat4 &m, const float s);

const mat2 operator /(const mat2 &m, const float s);
const mat3 operator /(const mat3 &m, const float s);
const mat4 operator /(const mat4 &m, const float s);

const mat2 operator /(const float s, const mat2 &m);
const mat3 operator /(const float s, const mat3 &m);
const mat4 operator /(const float s, const mat4 &m);

mat2 &operator /=(mat2 &m, const float s);
mat3 &operator /=(mat3 &m, const float s);
mat4 &operator /=(mat4 &m, const float s);

bool operator ==(const mat2 &m0, const mat2 &m1);
bool operator ==(const mat3 &m0, const mat3 &m1);
bool operator ==(const mat4 &m0, const mat4 &m1);

bool operator !=(const mat2 &m0, const mat2 &m1);
bool operator !=(const mat3 &m0, const mat3 &m1);
bool operator !=(const mat4 &m0, const mat4 &m1);



//-----------------------------------------------------------------------------
// special functions

// compute the determinant of a matrix
float determinant(const mat2 &m);
float determinant(const mat3 &m);

float invDeterminant(const mat2 &m);
float invDeterminant(const mat3 &m);


// compute the transpose of a matrix (flip values along diagonal)
const mat2 transpose(const mat2 &m);
const mat3 transpose(const mat3 &m);
const mat4 transpose(const mat4 &m);


// create axial rotations
const mat3 makeRotationX3(float radians);
const mat4 makeRotationX4(float radians);

const mat3 makeRotationY3(float radians);
const mat4 makeRotationY4(float radians);

const mat2 makeRotationZ2(float radians);
const mat3 makeRotationZ3(float radians);
const mat4 makeRotationZ4(float radians);

// create complex rotation from euler angles (radians)
const mat3 makeRotationEuler3XYZ(float rx, float ry, float rz);
const mat3 makeRotationEuler3XZY(float rx, float ry, float rz);
const mat3 makeRotationEuler3YXZ(float rx, float ry, float rz);
const mat3 makeRotationEuler3YZX(float rx, float ry, float rz);
const mat3 makeRotationEuler3ZXY(float rx, float ry, float rz);
const mat3 makeRotationEuler3ZYX(float rx, float ry, float rz);

const mat4 makeRotationEuler4XYZ(float rx, float ry, float rz);
const mat4 makeRotationEuler4XZY(float rx, float ry, float rz);
const mat4 makeRotationEuler4YXZ(float rx, float ry, float rz);
const mat4 makeRotationEuler4YZX(float rx, float ry, float rz);
const mat4 makeRotationEuler4ZXY(float rx, float ry, float rz);
const mat4 makeRotationEuler4ZYX(float rx, float ry, float rz);

// the euler angles are stored in order (XYZ) and the multiplication happens
//	in the order of the indices provided from right to left
const mat3 makeRotationEuler3(float rx, float ry, float rz, const unsigned int order[3]);
const mat3 makeRotationEuler3(float rx, float ry, float rz, const unsigned short order[3]);
const mat4 makeRotationEuler4(float rx, float ry, float rz, const unsigned int order[3]);
const mat4 makeRotationEuler4(float rx, float ry, float rz, const unsigned short order[3]);

// angle axis rotation
const mat3 makeRotationAngleAxis3(float radians, vec3 axis);
const mat4 makeRotationAngleAxis4(float radians, vec3 axis);

// create uniform scale
const mat2 makeScale2(float s);
const mat3 makeScale3(float s);
const mat4 makeScale4(float s);

// create non-uniform scale
const mat2 makeScale2(float sx, float sy);
const mat3 makeScale3(float sx, float sy, float sz);
const mat4 makeScale4(float sx, float sy, float sz);

// create translation transformation
const mat4 makeTranslation4(const vec3 &t);
const mat4 makeTranslation4(float tx, float ty, float tz);

// build and invert a homogeneous transformation
const mat4 makeTransform(const mat3 &r, const vec3 &t);
const mat4 makeTransform(const mat3 &r, const float s, const vec3 &t);
const mat4 makeTransform(const mat3 &r, const mat3 &s, const vec3 &t);

const mat4 makeRotateScale(const mat3 &r, const float s);
const mat4 makeRotateTranslate(const mat3 &r, const vec3 &t);
const mat4 makeScaleTranslate(const float s, const vec3 &t);

// compute the inverse matrix quickly for each type
const mat2 inverse(const mat2 &m);
const mat2 inverseNoScale(const mat2 &m);
const mat2 inverseUniformScale(const mat2 &m);

const mat3 inverse(const mat3 &m);
const mat3 inverseNoScale(const mat3 &m);
const mat3 inverseUniformScale(const mat3 &m);

const mat4 transformInverse(const mat4 &m);
const mat4 transformInverseNoScale(const mat4 &m);
const mat4 transformInverseUniformScale(const mat4 &m);

// utility to multiply 4D matrix with 3D vector
const vec3 multMat4Vec3(const mat4 &m, const vec3 &v);
const vec3 multMat4Vec3NoTranslate(const mat4 &m, const vec3 &v);

// utility to make basic projection matrix
const mat4 makePerspective(float fovyRadians, float aspectRatio, 
	float znear, float zfar);
const mat4 makePerspective(float left, float right, float bottom, float top, 
	float znear, float zfar);
const mat4 makeOrthographic(float width, float height, 
	float znear, float zfar);
const mat4 makeOrthographic(float left, float right, float bottom, float top, 
	float znear, float zfar);


#include "mat.inl"

}
}

using namespace bmath::mat;


#endif	// _BMATH_MAT_H