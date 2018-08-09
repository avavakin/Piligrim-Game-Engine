#include "mat4.h"
#include "math_func.h"

namespace piligrim {
	namespace math {



		mat4::mat4()
		{
		}



		mat4::mat4(float diagonal)
		{
			for (unsigned char i = 0; i < MAT4_N * MAT4_N; i++) {
				if (i % (MAT4_N + 1) != 0) {
					elements[i] = 0.0f;
					continue;
				}
				elements[i] = diagonal;
			}
		}



		mat4 mat4::identity()
		{
			return mat4(1.0f);
		}



		mat4 mat4::orthographic(float left, float right, float top, float bottom, float near, float far)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * MAT4_N] = 2.0f / (right - left);
			result.elements[1 + 1 * MAT4_N] = 2.0f / (top - bottom);
			result.elements[2 + 2 * MAT4_N] = -2.0f / (far - near);

			result.elements[0 + 3 * MAT4_N] = -(right + left) / (right - left);
			result.elements[1 + 3 * MAT4_N] = -(top + bottom) / (top - bottom);
			result.elements[2 + 3 * MAT4_N] = -(far + near) / (far - near);

			return result;
		}



		mat4 mat4::perspective(float fov, float aspectRatio, float near, float far)
		{
			mat4 result(1.0f);

			float q = 1.0f / tan(toRadians(0.5f * fov));
			float a = q / aspectRatio;

			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);

			result.elements[0 + 0 * MAT4_N] = a;
			result.elements[1 + 1 * MAT4_N] = q;
			result.elements[2 + 2 * MAT4_N] = b;
			result.elements[3 + 2 * MAT4_N] = -1.0f;
			result.elements[2 + 3 * MAT4_N] = c;

			return result;
		}



		mat4 mat4::translation(const vec3 & translation)
		{
			mat4 result(1.0f);
			
			result.elements[0 + 3 * MAT4_N] = translation.x;
			result.elements[1 + 3 * MAT4_N] = translation.y;
			result.elements[2 + 3 * MAT4_N] = translation.z;

			return result;
		}



		mat4 mat4::rotation(const vec3 & axis, float angle)
		{
			mat4 result(1.0f);

			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			float x_omc = x*omc;
			float y_omc = y*omc;
			float z_omc = z*omc;

			float x_y_omc = x_omc * y;
			float x_z_omc = x_omc * z;
			float y_z_omc = y_omc * z;

			float x_s = x*s;
			float y_s = y*s;
			float z_s = z*s;

			result.elements[0 + 0 * MAT4_N] = x_omc + c;
			result.elements[1 + 0 * MAT4_N] = x_y_omc + z_s;
			result.elements[2 + 0 * MAT4_N] = x_z_omc - y_s;

			result.elements[0 + 1 * MAT4_N] = x_y_omc - z_s;
			result.elements[1 + 1 * MAT4_N] = y_omc + c;
			result.elements[2 + 1 * MAT4_N] = y_z_omc + x_s;

			result.elements[0 + 2 * MAT4_N] = x_z_omc + y_s;
			result.elements[1 + 2 * MAT4_N] = y_z_omc - x_s;
			result.elements[2 + 2 * MAT4_N] = z_omc + c;

			return result;
		}



		mat4 mat4::scale(const vec3 & scale)
		{
			mat4 result(1.0f);

			result.elements[0 + 0 * MAT4_N] = scale.x;
			result.elements[1 + 1 * MAT4_N] = scale.y;
			result.elements[2 + 2 * MAT4_N] = scale.z;

			return result;
		}



		mat4 operator*(const mat4 & left, const mat4 & right)
		{
			mat4 result;

			for (unsigned char x = 0; x < MAT4_N; x++) {
				for (unsigned char y = 0; y < MAT4_N; y++) {
					result.elements[y + x * MAT4_N] = 0.0f;
					for (unsigned char e = 0; e < MAT4_N; e++) {
						result.elements[y + x * MAT4_N] += left.elements[y + e * MAT4_N] * right.elements[e + x * MAT4_N];
					}
				}
			}

			return result;
		}



		mat4 operator+(const mat4 & left, const mat4 & right)
		{
			mat4 result;

			for (unsigned char i = 0; i < MAT4_N * MAT4_N; i++) {
				result.elements[i] = left.elements[i] + right.elements[i];
			}

			return result;
		}



		mat4 operator-(const mat4 & left, const mat4 & right)
		{
			mat4 result;

			for (unsigned char i = 0; i < MAT4_N * MAT4_N; i++) {
				result.elements[i] = left.elements[i] - right.elements[i];
			}

			return result;
		}



		mat4 & mat4::operator*=(const mat4 & right)
		{
			*this = *this * right;

			return *this;
		}



		mat4 & mat4::operator+=(const mat4 & right)
		{
			*this = *this + right;

			return *this;
		}



		mat4 & mat4::operator-=(const mat4 & right)
		{
			*this = *this - right;

			return *this;
		}



		std::ostream & operator<<(std::ostream & s, const mat4 & matr)
		{
			for (unsigned char x = 0; x < MAT4_N; x++) {
				for (unsigned char y = 0; y < MAT4_N; y++) {
					s << matr.elements[x + y*MAT4_N] << " ";
				}
				s << std::endl;
			}

			return s;
		}



	}
}