#include "fastmath.h"

double piligrim::math::FastMath::sin(double alpha)
{ // x - x^3/6 + x^5/120 - x^7/5040 + x^9/362880 - x^11/39916800 + x^13/6227020800 - x^15/1307674368000
	double squaredX = alpha*alpha;
	double currentX = alpha;
	double res = currentX;

	currentX *= squaredX;
	res -= currentX / 6;

	currentX *= squaredX;
	res += currentX / 120;

	currentX *= squaredX;
	res -= currentX / 5040;

	currentX *= squaredX;
	res += currentX / 362880;

	currentX *= squaredX;
	res -= currentX / 39916800;

	currentX *= squaredX;
	res += currentX / 6227020800;

	currentX *= squaredX;
	res -= currentX / 1307674368000;

	return res;
}

float piligrim::math::FastMath::sinf(float alpha)
{ // x - x^3/6 + x^5/120 - x^7/5040 + x^9/362880 - x^11/39916800 + x^13/6227020800 - x^15/1307674368000
	float squaredX = alpha*alpha;
	float currentX = alpha;
	float res = currentX;

	currentX *= squaredX;
	res -= currentX / 6;

	currentX *= squaredX;
	res += currentX / 120;

	currentX *= squaredX;
	res -= currentX / 5040;

	currentX *= squaredX;
	res += currentX / 362880;

	currentX *= squaredX;
	res -= currentX / 39916800;

	currentX *= squaredX;
	res += currentX / 6227020800;

	currentX *= squaredX;
	res -= currentX / 1307674368000;

	return res;
}

double piligrim::math::FastMath::cos(double alpha)
{ // 1 - x^2/2 + x^4/24 - x^6/720 + x^8/40320 - x^10/3628800 + x^12/479001600 - x^14/87178291200 + x^16/20922789888000
	double squaredX = alpha*alpha;
	double currentX = 1;
	double res = currentX;

	currentX *= squaredX;
	res -= currentX / 2;

	currentX *= squaredX;
	res += currentX / 24;

	currentX *= squaredX;
	res -= currentX / 720;

	currentX *= squaredX;
	res += currentX / 40320;

	currentX *= squaredX;
	res -= currentX / 3628800;

	currentX *= squaredX;
	res += currentX / 479001600;

	currentX *= squaredX;
	res -= currentX / 87178291200;

	currentX *= squaredX;
	res += currentX / 20922789888000;

	return res;
}

float piligrim::math::FastMath::cosf(float alpha)
{ // 1 - x^2/2 + x^4/24 - x^6/720 + x^8/40320 - x^10/3628800 + x^12/479001600 - x^14/87178291200 + x^16/20922789888000
	float squaredX = alpha*alpha;
	float currentX = 1;
	float res = currentX;

	currentX *= squaredX;
	res -= currentX / 2;

	currentX *= squaredX;
	res += currentX / 24;

	currentX *= squaredX;
	res -= currentX / 720;

	currentX *= squaredX;
	res += currentX / 40320;

	currentX *= squaredX;
	res -= currentX / 3628800;

	currentX *= squaredX;
	res += currentX / 479001600;

	currentX *= squaredX;
	res -= currentX / 87178291200;

	currentX *= squaredX;
	res += currentX / 20922789888000;

	return res;
}
