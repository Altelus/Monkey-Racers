/*
	Vector classes
	By Dan Buckstein
	Standalone vector classes.
	Contains structures for 2D, 3D and 4D vector, with associated functions
		and operators.
*/


#ifndef _BMATH_VEC_H
#define _BMATH_VEC_H


#include "BMath/util.h"


namespace bmath
{
namespace vec
{


union vec2;
union vec3;
union vec4;


//-----------------------------------------------------------------------------
// structures

union vec2
{
	// ctor
	vec2();
	explicit vec2(float X, float Y);
	explicit vec2(float V);
	explicit vec2(const float *Vp);
	explicit vec2(const vec3 &v3);
	explicit vec2(const vec4 &v4);

	// set and reset
	vec2 &set();
	vec2 &set(float X, float Y);
	vec2 &set(float V);
	vec2 &set(const float *Vp);
	vec2 &set(const vec3 &v3);
	vec2 &set(const vec4 &v4);

	// access values
	const float operator[](unsigned char r) const;
	float &operator[](unsigned char r);

	// data
	struct { float x,y; };
	struct { float s,t; };
	float v[2];
};
static const vec2 v2zero;
static const vec2 v2x(1, 0);
static const vec2 v2y(0, 1);


union vec3
{
	// ctor
	vec3();
	explicit vec3(float X, float Y, float Z);
	explicit vec3(float V);
	explicit vec3(const float *Vp);
	explicit vec3(const vec2 &v2, float Z=0.0f);
	explicit vec3(const vec4 &v4);

	// set and reset
	vec3 &set();
	vec3 &set(float X, float Y, float Z);
	vec3 &set(float V);
	vec3 &set(const float *Vp);
	vec3 &set(const vec2 &v2, float Z=0.0f);
	vec3 &set(const vec4 &v4);

	// access values
	const float operator[](unsigned char r) const;
	float &operator[](unsigned char r);

	// data
	struct { float x,y,z; };
	struct { float r,g,b; };
	struct { float s,t,p; };
	struct { vec2 xy; };
	float v[3];
};
static const vec3 v3zero;
static const vec3 v3x(1, 0, 0);
static const vec3 v3y(0, 1, 0);
static const vec3 v3z(0, 0, 1);


union vec4
{
	// ctor
	vec4();
	explicit vec4(float X, float Y, float Z, float W);
	explicit vec4(float V);
	explicit vec4(const float *Vp);
	explicit vec4(const vec2 &v2, float Z=0.0f, float W=0.0f);
	explicit vec4(const vec3 &v3, float W=0.0f);

	// set and reset
	vec4 &set();
	vec4 &set(float X, float Y, float Z, float W);
	vec4 &set(float V);
	vec4 &set(const float *Vp);
	vec4 &set(const vec2 &v2, float Z=0.0f, float W=0.0f);
	vec4 &set(const vec3 &v3, float W=0.0f);

	// access values
	const float operator[](unsigned char r) const;
	float &operator[](unsigned char r);

	// data
	struct { float x,y,z,w; };
	struct { float r,g,b,a; };
	struct { float s,t,p,q; };
	struct { vec2 xy; };
	struct { vec3 xyz; };
	float v[4];
};
static const vec4 v4zero;
static const vec4 v4x(1, 0, 0, 0);
static const vec4 v4y(0, 1, 0, 0);
static const vec4 v4z(0, 0, 1, 0);
static const vec4 v4w(0, 0, 0, 1);



//-----------------------------------------------------------------------------
// operators

float dot(const vec2 &v0, const vec2 &v1);
float dot(const vec3 &v0, const vec3 &v1);
float dot(const vec4 &v0, const vec4 &v1);


const vec2 operator +(const vec2 &v0, const vec2 &v1);
const vec3 operator +(const vec3 &v0, const vec3 &v1);
const vec4 operator +(const vec4 &v0, const vec4 &v1);

vec2 &operator +=(vec2 &v0, const vec2 &v1);
vec3 &operator +=(vec3 &v0, const vec3 &v1);
vec4 &operator +=(vec4 &v0, const vec4 &v1);

const vec2 operator +(const vec2 &v);
const vec3 operator +(const vec3 &v);
const vec4 operator +(const vec4 &v);

const vec2 operator -(const vec2 &v0, const vec2 &v1);
const vec3 operator -(const vec3 &v0, const vec3 &v1);
const vec4 operator -(const vec4 &v0, const vec4 &v1);

vec2 &operator -=(vec2 &v0, const vec2 &v1);
vec3 &operator -=(vec3 &v0, const vec3 &v1);
vec4 &operator -=(vec4 &v0, const vec4 &v1);

const vec2 operator -(const vec2 &v);
const vec3 operator -(const vec3 &v);
const vec4 operator -(const vec4 &v);

const vec2 operator *(const vec2 &v, const float s);
const vec3 operator *(const vec3 &v, const float s);
const vec4 operator *(const vec4 &v, const float s);

const vec2 operator *(const float s, const vec2 &v);
const vec3 operator *(const float s, const vec3 &v);
const vec4 operator *(const float s, const vec4 &v);

vec2 &operator *=(vec2 &v, const float s);
vec3 &operator *=(vec3 &v, const float s);
vec4 &operator *=(vec4 &v, const float s);

const vec2 operator /(const vec2 &v, const float s);
const vec3 operator /(const vec3 &v, const float s);
const vec4 operator /(const vec4 &v, const float s);

const vec2 operator /(const float s, const vec2 &v);
const vec3 operator /(const float s, const vec3 &v);
const vec4 operator /(const float s, const vec4 &v);

vec2 &operator /=(vec2 &v, const float s);
vec3 &operator /=(vec3 &v, const float s);
vec4 &operator /=(vec4 &v, const float s);

bool operator ==(const vec2 &v0, const vec2 &v1);
bool operator ==(const vec3 &v0, const vec3 &v1);
bool operator ==(const vec4 &v0, const vec4 &v1);

bool operator !=(const vec2 &v0, const vec2 &v1);
bool operator !=(const vec3 &v0, const vec3 &v1);
bool operator !=(const vec4 &v0, const vec4 &v1);


//-----------------------------------------------------------------------------
// special operators
// component-wise multiplication with vectors, and addition with scalars
// made for convenience; because we know how to use vectors, we know that we 
//	can bend the rules a little bit...

const vec2 operator *(const vec2 &v0, const vec2 &v1);
const vec3 operator *(const vec3 &v0, const vec3 &v1);
const vec4 operator *(const vec4 &v0, const vec4 &v1);

vec2 &operator *=(vec2 &v0, const vec2 &v1);
vec3 &operator *=(vec3 &v0, const vec3 &v1);
vec4 &operator *=(vec4 &v0, const vec4 &v1);

const vec2 operator /(const vec2 &v0, const vec2 &v1);
const vec3 operator /(const vec3 &v0, const vec3 &v1);
const vec4 operator /(const vec4 &v0, const vec4 &v1);

vec2 &operator /=(vec2 &v0, const vec2 &v1);
vec3 &operator /=(vec3 &v0, const vec3 &v1);
vec4 &operator /=(vec4 &v0, const vec4 &v1);


const vec2 operator +(const vec2 &v, const float s);
const vec3 operator +(const vec3 &v, const float s);
const vec4 operator +(const vec4 &v, const float s);

const vec2 operator +(const float s, const vec2 &v);
const vec3 operator +(const float s, const vec3 &v);
const vec4 operator +(const float s, const vec4 &v);

vec2 &operator +=(vec2 &v, const float s);
vec3 &operator +=(vec3 &v, const float s);
vec4 &operator +=(vec4 &v, const float s);

const vec2 operator -(const vec2 &v, const float s);
const vec3 operator -(const vec3 &v, const float s);
const vec4 operator -(const vec4 &v, const float s);

const vec2 operator -(const float s, const vec2 &v);
const vec3 operator -(const float s, const vec3 &v);
const vec4 operator -(const float s, const vec4 &v);

vec2 &operator -=(vec2 &v, const float s);
vec3 &operator -=(vec3 &v, const float s);
vec4 &operator -=(vec4 &v, const float s);



//-----------------------------------------------------------------------------
// special functions

// rotate a 2D vector given an angle in radians, or the trigonometry parts 
//	required to perform the rotation: cos(a) and sin(a)
const vec2 rotate(const float angle, const vec2 &v);
const vec2 rotate(const float cosine, const float sine, const vec2 &v);

// cross product for 3D vectors
const vec3 cross(const vec3 &v0, const vec3 &v1);
const vec3 crossNormalize(const vec3 &v0, const vec3 &v1);

// compute the normal given three spatial points
// normal is equal to the normalized version of (v1-v0)x(v2-v0)
const vec3 computeTriNormal(const vec3 &v0, const vec3 &v1, const vec3 &v2);

// compute the area of the triangle given three spatial points
// equal to the magnitude of (v1-v0)x(v2-v0)
float computeTriArea(const vec3 &v0, const vec3 &v1, const vec3 &v2);

// combination of the above two functions
float computeTriAreaNormal(const vec3 &v0, const vec3 &v1, const vec3 &v2, vec3 &normal);

// Gram-Schmidt orthogonalization algorithm
void GramSchmidt(const vec2 &base, vec2 &v);
void GramSchmidt(const vec3 &base, vec3 &v);
void GramSchmidt(const vec3 &base, vec3 &v0, vec3 &v1);

// compute the radius-to-edge-radius ratio of two points separated by a 
//	certain amount of radians; for 2D the ratio is computed between the point 
//	and the center of the edge, in 3D the center of the face is used
float edgeToPointRadius(double separationRadians);
float pointToEdgeRadius(double separationRadians);
float edgeToPointRadius(double separationRadians, float scalar);
float pointToEdgeRadius(double separationRadians, float scalar);

float faceToPointRadius(double sepAzimuth, double sepElevation, float scalar);
float pointToFaceRadius(double sepAzimuth, double sepElevation, float scalar);
float faceToPointRadius(double sepAzimuth, double sepElevation, float scalar);
float pointToFaceRadius(double sepAzimuth, double sepElevation, float scalar);


#include "vec.inl"

}
}

using namespace bmath::vec;


#endif	// _BMATH_VEC_H