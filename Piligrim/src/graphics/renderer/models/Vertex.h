#pragma once
#include "../../../math/math.h"
namespace piligrim {
	namespace graphics {
		class Vertex {
		private:
			math::vec3 position_;
			math::vec3 color_;
			math::vec2 textCoord_;
		public:
			Vertex();
			Vertex(const math::vec3& position);
			Vertex(const math::vec3& position, const math::vec3& color);
			Vertex(const math::vec3& position, const math::vec3& color, const math::vec2& textCoord);

			math::vec3 getPosition() const;
			math::vec3 getColor() const;
			math::vec2 getTextCoord() const;

			void setPos(const math::vec3& position);
			void setColor(const math::vec3& color);
			void setTextCoord(const math::vec2& textCoord);

			friend Vertex operator+(const Vertex& left, const Vertex& right);
			friend Vertex operator-(const Vertex& left, const Vertex& right);
			Vertex& operator+=(const Vertex& right);
			Vertex& operator-=(const Vertex& right);

			double distTo(const Vertex &other) const { return this->position_.distTo(other.position_); }

		};
	}
}