/**
 \file	Macros.h

 \brief	Declares the macros class.
 */


#include <Box2D/Box2D.h>
#include <string>
#include <cmath>

/**
 \brief	A macro that defines scale.
 */

#define SCALE 100
/**
 \brief	A macro that defines radians to degrees.

 \param	a	The void to process.
 */

#define RAD_TO_DEG(a) a*180.f/b2_pi

/**
 \brief	A macro that defines degrees to radians.

 \param	a	The void to process.
 */

#define DEG_TO_RAD(a) a*b2_pi/180.f

/**
 \brief	A macro that defines round to nearest f.

 \param	a	The void to process.
 */

#define ROUND_TO_NEAREST_F(a) floorf(a*SCALE +0.5)/SCALE

/**
 \brief	A macro that defines scale up.

 \param	a	The void to process.
 */

#define SCALE_UP(a) a * SCALE

/**
 \brief	A macro that defines scale down.

 \param	a	The void to process.
 */

#define SCALE_DOWN(a) a / SCALE

/**
// End of Macros.h
 */


#pragma once
static std::string path;