

#ifndef _QUATERNION_H
#define _QUATERNION_H


// need vector (THIS IS JUST A STAND-IN, 
//	USE A REAL MATH LIBRARY!)
#include "Include/SFML/Graphics.hpp"


// simple quaternion class
// used for rotations and orientations
class Quaternion
{
public: 

	// construct as IDENTITY
	Quaternion()
	{
		w = 1.0f;
		x = y = z = 0.0f;
	}


	// construct as four numbers
	Quaternion(float _w, float _x, float _y, float _z)
	{
		w = _w;
		x = _x;
		y = _y;
		z = _z;
	}


	// construct as angle-axis (angle in radians)
	// **** CHANGE THIS TO REFLECT THE MATH LIBRARY YOU ARE USING!
	Quaternion(float angleRadians, 
			   const sf::Vector3f axis)
	{
		// **** IMPLEMENT THIS!
	}


	// get components
	inline float GetW() const { return w; }
	inline float GetScalar() const { return w; }

	inline float GetX() const { return x; }
	inline float GetY() const { return y; }
	inline float GetZ() const { return z; }

	// **** CHANGE THIS TOO!
	inline sf::Vector3f GetVector() const { return u; }


	// mathematical operations

	// get the CONJUGATE of this quaternion
	inline Quaternion GetConjugate() const
	{
		return Quaternion(w, -x, -y, -z);
	}


	// you can add, subtract and scale quaternions, too!
	inline Quaternion operator+(const Quaternion q) const
	{
		return Quaternion(w + q.w, x + q.x, y + q.y, z + q.z);
	}
	inline Quaternion operator-(const Quaternion q) const
	{
		return Quaternion(w - q.w, x - q.x, y - q.y, z - q.z);
	}
	inline Quaternion operator*(const float scalar) const
	{
		return Quaternion(w*scalar, x*scalar, y*scalar, z*scalar);
	}


	// **** NEED TO FILL THESE OUT!!!!

	// **** multiply with another quaternion
	inline Quaternion operator*(const Quaternion q2) const
	{
		const Quaternion q1 = *this;

		// **** take note of the formula we use: 
		//	q1 * q2: implies that the argument above is on the right
		// **** remember that multiplication is not commutative, so 
		//	make sure you are doing this right!


		return Quaternion();
	}


	// **** function to make this an angle-axis quaternion
	//	used for rotations
	inline Quaternion &MakeAngleAxis(float angleRadians, 
									 const sf::Vector3f axis)
	{
		// **** IMPLEMENT

		return *this;
	}


	// **** use this quaternion to rotate a vector
	//	again, change the argument to reflect the math library
	inline sf::Vector3f RotateVector(const sf::Vector3f vec) const
	{
		return sf::Vector3f();
	}


private: 

	// scalar component
	float w;

	// vector component
	// **** PROGRAMMING CONCEPT: UNION!
	// **** TAKE NOTES!
	union
	{
		struct {
			float x, y, z;
		};
		struct {
			sf::Vector3f u;
		};
	};

};




// **** SLERP
// implement this!
//** (sin(1-t)theta)/sin theta)*p0 +
//   (sin(t)theta)/sin theta)*p1
//   a.b = |a||b| cos theta
//case if p0 = p1 or parallel
inline Quaternion SLERP(const Quaternion q0, 
						const Quaternion q1, 
						const float t)
{
	// **** implement slerp

	return Quaternion();
}



#endif	// _QUATERNION_H