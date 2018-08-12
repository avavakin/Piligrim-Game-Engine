#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

namespace piligrim {
	namespace math {

		inline float toRadians(float angle)
		{
			return angle * (M_PI / 180.0f);
		}

		inline float toDegrees(float angle)
		{
			return angle * (180.0f / M_PI);
		}

	}
}