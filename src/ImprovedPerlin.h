#ifndef IMPROVED_PERLIN
#define IMPROVED_PERLIN
// noise1234
//
// Author: Stefan Gustavson, 2003-2005
// Contact: stegu@itn.liu.se
//
// This code was GPL licensed until February 2011.
// As the original author of this code, I hereby
// release it into the public domain.
// Please feel free to use it for whatever you want.
// Credit is appreciated where appropriate, and I also
// appreciate being told where this code finds any use,
// but you may do as you like.

/** \file
		\brief Declares the "noise1" through "noise4" functions for Perlin noise.
		\author Stefan Gustavson (stegu@itn.liu.se)
*/

/*
 * This is a backport to C of my improved noise class in C++.
 * It is highly reusable without source code modifications.
 *
 * Note:
 * Replacing the "float" type with "double" can actually make this run faster
 * on some platforms. A templatized version of Noise1234 could be useful.
 */

#include <Arduino.h>

class ImprovedPerlin
{
public:
	ImprovedPerlin();
	/** 1D, 2D, 3D and 4D float Perlin noise, SL "noise()"
	 */
	float noise1(const float x) const;
	float noise2(const float x, const float y) const;
	float noise3(const float x, const float y, const float z) const;
	float noise4(const float x, const float y, const float z, const float w) const;

	/** 1D, 2D, 3D and 4D float Perlin periodic noise, SL "pnoise()"
	 */
	float pnoise1(const float x, const int px) const;
	float pnoise2(const float x, const float y, const int px, const int py) const;
	float pnoise3(const float x, const float y, const float z, const int px, const  int py, const  int pz) const;
	float pnoise4(const float x, const float y, const float z, const float w, const int px, const int py, const int pz, const int pw) const ;

	void setSeed_unsafe(const uint32_t seed_in);
private:
	void reset_perm();
	uint8_t member_perm[512];
};

#endif