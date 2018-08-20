#pragma once

struct vec3
{
	float x;
	float y;
	float z;

	vec3();
	vec3(float value);
	vec3(float x, float y, float z);

	double scalProduct(const vec3& right) const;
	vec3 crossProduct(const vec3& right) const;
	double length() const;
	double distTo(const vec3& right) const;
	vec3 getNormalize() const;

	static vec3 ox();
	static vec3 oy();
	static vec3 oz();

	friend vec3 operator +(const vec3& left, const vec3& right);
	friend vec3 operator -(const vec3& left, const vec3& right);
	friend vec3 operator *(const vec3& left, double scal);
	friend vec3 operator /(const vec3& left, double scal);
	friend vec3 operator -(const vec3& vec);

	vec3& operator +=(const vec3& right);
	vec3& operator -=(const vec3& right);
	vec3& operator *=(double scal);
	vec3& operator /=(double scal);

	friend bool operator==(const vec3& left, const vec3& right);
	friend bool operator!=(const vec3& left, const vec3& right);
};