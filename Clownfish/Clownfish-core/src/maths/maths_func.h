#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

namespace clownfish {
	namespace maths {

		inline float toRadiance(float degrees)
		{
			return degrees * (M_PI / 180);
		}
	}
}