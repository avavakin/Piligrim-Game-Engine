#include "Vertex.h"
namespace piligrim {
	namespace graphics {


		Vertex::Vertex()
		{
		}

		Vertex::Vertex(const math::vec3 & position)
		{
			position_ = position;
		}

		Vertex::Vertex(const math::vec3 & position, const math::vec3 & color) 
			: Vertex(position)
		{
			color_ = color;
		}

		Vertex::Vertex(const math::vec3 & position, const math::vec3 & color, const math::vec2 & textCoord)
			: Vertex(position, color)
		{
			textCoord_ = textCoord;
		}
		

		math::vec3 Vertex::getPosition() const
		{
			return position_;
		}

		math::vec3 Vertex::getColor() const
		{
			return color_;
		}

		math::vec2 Vertex::getTextCoord() const
		{
			return textCoord_;
		}

		void Vertex::setPos(const math::vec3 & position)
		{
			position_ = position;
		}

		void Vertex::setColor(const math::vec3 & color)
		{
			color_ = color;
		}

		void Vertex::setTextCoord(const math::vec2 & textCoord)
		{
			textCoord_ = textCoord;
		}

		Vertex operator+(const Vertex & left, const Vertex & right)
		{
			return Vertex(left.position_ + right.position_);
		}

		Vertex operator-(const Vertex & left, const Vertex & right)
		{
			return Vertex(left.position_ - right.position_);
		}

		Vertex & Vertex::operator+=(const Vertex & right)
		{
			*this = *this + right;

			return *this;
		}

		Vertex & Vertex::operator-=(const Vertex & right)
		{
			*this = *this - right;

			return *this;
		}

	}
}