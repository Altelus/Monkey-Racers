#ifndef _ANIMATION_MATH_H
#define _ANIMATION_MATH_H

#include "Include/SFML/Graphics.hpp"

template <typename lerpClass>
inline lerpClass LERP(lerpClass p0, lerpClass p1, float t)
{
	// formula 1 (racing) overload -,+,*
	return ((p1 - p0)*t + p0);

	// formula 2 (not racing) overload +,*
	//result = (1.0f - t)*p0 + (t)*p1;
}

template <typename lerpClass>
inline lerpClass BLEND(const lerpClass p0, const lerpClass p1, const float t)
{
	result = (1.0f - t)*p0 + (t)*p1;
}

template <typename catmullromClass>
inline catmullromClass CatmullRom(catmullromClass p_i_1, catmullromClass p_i,
						catmullromClass p_i1, catmullromClass p_i2,
						float t)
{
	return //0.5f * 
		( p_i*2 
		+ (p_i_1*-1 + p_i1) * t
		+ (p_i_1* 2 - p_i*5 + p_i1*4 - p_i2)*t*t
		+ (p_i_1*-1 + p_i*3 - p_i1*3 + p_i2)*t*t*t) *0.5f;
}

template <typename bezierClass>
inline bezierClass Bezier(const bezierClass p[], 
	const unsigned int degree, //segments, # of points - 1
	const float t)
{
	if (degree == 0)
		return *p;//p[0]
	else
		return LERP(Bezier(p, degree-1, t), Bezier(p+1, degree-1, t), t);
}


#endif