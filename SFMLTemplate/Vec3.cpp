//Brent Cowan 2013

#include "Engine.h"

float Vec3::sinAngle = 0.0f;
float Vec3::cosAngle = 0.0f;
Vec3 Vec3::tempV;

Vec3::Vec3()
{
   x = 0.0f;
   y = 0.0f;
   z = 0.0f;
}

Vec3::Vec3(float X, float Y, float Z)
{
   x = X;
   y = Y;
   z = Z;
}

Vec3::Vec3(const Vec3 &v)
{
   x = v.x;
   y = v.y;
   z = v.z;
}

bool Vec3::operator==(const Vec3 &v)
{
	if(x==v.x && y==v.y && z==v.z)return true; else return false;
}

void Vec3::operator=(const Vec3 &v)
{
   x = v.x;
   y = v.y;
   z = v.z;
}

void Vec3::operator+=(const Vec3 &v)
{
   x += v.x;
   y += v.y;
   z += v.z;
}

void Vec3::operator-=(const Vec3 &v)
{
   x -= v.x;
   y -= v.y;
   z -= v.z;
}

void Vec3::operator/=(const Vec3 &v)
{
   x /= v.x;
   y /= v.y;
   z /= v.z;
}

void Vec3::operator*=(const Vec3 &v)
{
   x *= v.x;
   y *= v.y;
   z *= v.z;
}

Vec3 Vec3::operator+(const Vec3 &v2)
{
   return Vec3(x + v2.x, y + v2.y, z + v2.z);
}

Vec3 Vec3::operator-(const Vec3 &v2)
{
   return Vec3(x - v2.x, y - v2.y, z - v2.z);
}

Vec3 Vec3::operator/(const Vec3 &v2)
{
   return Vec3(x / v2.x, y / v2.y, z / v2.z);
}


Vec3 Vec3::operator*(const Vec3 &v2)
{
   return Vec3(x * v2.x, y * v2.y, z * v2.z);
}

Vec3 Vec3::operator/(float f)
{
   return Vec3(x / f, y / f, z / f);
}

Vec3 Vec3::operator*(float f)
{
   return Vec3(x * f, y * f, z * f);
}

Vec3 Vec3::Random()
{
	Vec3 temp;
	temp.x = float(rand()%3001)-1500.0f;
	temp.y = float(rand()%3001)-1500.0f;
	temp.z = float(rand()%3001)-1500.0f;
	temp.Normalize();
	return temp;
}

void Vec3::Negate()
{
   x = -x; y = -y; z = -z;
}

float Vec3::Dot(const Vec3 &v)
{
   return x * v.x + y * v.y + z * v.z;
}


float Vec3::GetLength()
{
   return (float)sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::Normalize()
{
   float len = sqrt(x * x + y * y + z * z);

   if(len <= 0.00001f) {return Vec3(0.0f, 1.0f, 0.0f);}

   len = 1.0f / len;

   return Vec3(x*len, y*len, z*len);
}

Vec3 Vec3::Cross(const Vec3 &v)
{
   return Vec3(y * v.z - z * v.y,
                   z * v.x - x * v.z,
                   x * v.y - y * v.x);
}

//rotations
void Vec3::RotateX(float angle)
{
	sinAngle = sin(DTR*angle);
	cosAngle = cos(DTR*angle);
	
	y = y*cosAngle - z*sinAngle;
	z = y*sinAngle + z*cosAngle;
}

void Vec3::RotateY(float angle)
{
	sinAngle = sin(DTR*angle);
	cosAngle = cos(DTR*angle);

	x =  x*cosAngle + z*sinAngle;
	z = -x*sinAngle + z*cosAngle;
}

void Vec3::RotateZ(float angle)
{
	sinAngle = sin(DTR*angle);
	cosAngle = cos(DTR*angle);
	
	x = x*cosAngle - y*sinAngle;
	y = x*sinAngle + y*cosAngle;
}

void Vec3::PolarToVector(float azemuth, float elevation, float distance)
{
	sinAngle = azemuth*DTR;
	cosAngle = elevation*DTR;

	tempV.x = sin(sinAngle);
	tempV.z = cos(sinAngle)*(-1.0f);
	tempV.y = cos(cosAngle);

	x = tempV.x * tempV.y * distance;
	z = tempV.z * tempV.y * distance;
	y = sin(cosAngle)*(-1.0f) * distance;
}

Vec3 Vec3::VectorToPolar(Vec3 target)
{
	Vec3 output;

	output.y = 180.0f-(atan2(target.x, target.z)*RTD);

	if(output.y<0.0f){output.y+=360.0f;}

	tempV = target;
	tempV.y = 0.0f;
	output.x = (atan2(tempV.GetLength(), target.y)*RTD)-90.0f;

	if(output.x<0.0f){output.x+=360.0f;}

	output.z = (float)sqrt(target.x * target.x + target.y * target.y + target.z * target.z);

	return output;
}