//Brent Cowan 2013

#ifndef _VEC2_
#define _VEC2_

class Vec2
{
public:
	Vec2();
	Vec2(float X, float Y);
	Vec2(const Vec2 &v);

	bool operator==(const Vec2 &v);
	void operator=(const Vec2 &v);
	void operator+=(const Vec2 &v);
	void operator-=(const Vec2 &v);
	void operator/=(const Vec2 &v);
	void operator*=(const Vec2 &v);
	Vec2 operator+(const Vec2 &v2);
	Vec2 operator-(const Vec2 &v2);      
	Vec2 operator/(const Vec2 &v2);
	Vec2 operator*(const Vec2 &v2);
	Vec2 operator/(float f);
	Vec2 operator*(float f);

	void  Rotate(float angle);
	float Dot(const Vec2 &v);
	float GetLength();
	Vec2  Normalize();
	Vec2  AngleToVector(float angle);
	float VectorToAngle(const Vec2 &v);
	Vec2  Perp();
	float GetLengthSq();
	void  Reflect(Vec2 &norm);
	void  SetLength(float length);

	float x, y;
};

#endif