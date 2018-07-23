#pragma once

namespace piligrim {
	namespace math {
		class FastMath
		{
		public:
			// sin and cos make by Taylor approximation | sin - 15 degree; cos - 16 degree
			static double sin(double alpha);
			static float sinf(float alpha);

			static double cos(double alpha);
			static float cosf(float alpha);


		};
	}
}