#include "Engine.h"

Vec2::Vec2()
{
   x = 0.0f;
   y = 0.0f;
}

Vec2::Vec2(float X, float Y)
{
   x = X;
   y = Y;
}


Vec2::Vec2(const Vec2 &v)
{
   x = v.x;
   y = v.y;
}

bool Vec2::operator==(const Vec2 &v)
{
	if(x==v.x && y==v.y)return true; else return false;
}

void Vec2::operator=(const Vec2 &v)
{
   x = v.x; y = v.y;
}


void Vec2::operator+=(const Vec2 &v)
{
   x += v.x; y += v.y;
}


void Vec2::operator-=(const Vec2 &v)
{
   x -= v.x; y -= v.y;
}


void Vec2::operator/=(const Vec2 &v)
{
   x /= v.x; y /= v.y;
}


void Vec2::operator*=(const Vec2 &v)
{
   x *= v.x; y *= v.y;
}


Vec2 Vec2::operator+(const Vec2 &v2)
{
   return Vec2(x + v2.x, y + v2.y);
}


Vec2 Vec2::operator-(const Vec2 &v2)
{
   return Vec2(x - v2.x, y - v2.y);
}


Vec2 Vec2::operator/(const Vec2 &v2)
{
   return Vec2(x / v2.x, y / v2.y);
}


Vec2 Vec2::operator*(const Vec2 &v2)
{
   return Vec2(x * v2.x, y * v2.y);
}

Vec2 Vec2::operator/(float f)
{
   return Vec2(x / f, y / f);
}


Vec2 Vec2::operator*(float f)
{
   return Vec2(x * f, y * f);
}

void Vec2::Rotate(float angle)
{
	float rad = angle*DTR;
	float tempX = cos(rad)*x - sin(rad)*y;
	y = sin(rad)*x + cos(rad)*y;
	x = tempX;
}

float Vec2::Dot(const Vec2 &v)
{
   return x * v.x + y * v.y;
}


float Vec2::GetLength()
{
   return (float)sqrt(x * x + y * y);
}


Vec2 Vec2::Normalize()
{
   float len = sqrt(x * x + y * y);

   if(len <= 0.00001f)
   {
	   return Vec2(0.0f, 1.0f);
   }
   else
   {
		len = 1.0f / len;
		return Vec2(x*len, y*len);
   }
}

Vec2 Vec2::AngleToVector(float angle)
{
	return Vec2(cos(angle*DTR), sin(angle*DTR));
}

float Vec2::VectorToAngle(const Vec2 &v)
{
	return atan2(v.y, v.x)*RTD;
}

Vec2 Vec2::Perp()
{
  return Vec2(-y, x);
}

float Vec2::GetLengthSq()
{
  return (x * x + y * y);
}

void Vec2::Reflect(Vec2& norm)
{
  *this += (norm*-1.0f) * (this->Dot(norm)*2.0f);
}

void Vec2::SetLength(float length)
{
	Normalize();
	x *= length;
	y *= length;
}
