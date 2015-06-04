//Brent Cowan 2013

#ifndef _VEC3_
#define _VEC3_

class Vec3
{
private:
	static float sinAngle;
	static float cosAngle;
	static Vec3 tempV;

public:
	Vec3();
	Vec3(float X, float Y, float Z);
	Vec3(const Vec3 &v);

	bool operator==(const Vec3 &v);
	void operator=(const Vec3 &v);
	void operator+=(const Vec3 &v);
	void operator-=(const Vec3 &v);
	void operator/=(const Vec3 &v);
	void operator*=(const Vec3 &v);

	Vec3 operator+(const Vec3 &v2);
	Vec3 operator-(const Vec3 &v2);      
	Vec3 operator/(const Vec3 &v2);
	Vec3 operator*(const Vec3 &v2);

	Vec3 operator/(float f);
	Vec3 operator*(float f);

	void Negate();
	Vec3 Random();
	float Dot(const Vec3 &v);
	float GetLength();

	Vec3 Normalize();
	Vec3 Cross(const Vec3 &v);

	//rotations
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);
	void PolarToVector(float azemuth, float elevation, float distance);
	Vec3 VectorToPolar(Vec3 target);

	float x, y, z;
};

#endif