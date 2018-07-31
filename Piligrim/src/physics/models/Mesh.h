#pragma once
#include "../../math/math.h"
#include "../../graphics/scenegraph/isceneobject.h"
#include "../../graphics/buffers/vertexarray.h"
#include "../../graphics/buffers/buffer.h"
#include <vector>
namespace piligrim {
	namespace physics {

		class Point {
		private:
			math::vec3 pos;
			math::vec4 color;
			math::vec2 textCoord;
		public:
			Point() {}
			Point(const math::vec3& pos)
				:pos(pos) {}
			Point(const math::vec3& pos, const math::vec4& color)
				:pos(pos), color(color)	{}
			Point(const math::vec3& pos, const math::vec4& color, const math::vec2& textCoord)
				:pos(pos), color(color), textCoord(textCoord) {}

			inline math::vec3 getPos() const { return pos; }
			inline math::vec4 getColor() const { return color; }
			inline math::vec2 getTextCoord() const { return textCoord; }

			inline void setPos(const math::vec3& pos) { this->pos = pos; }
			inline void setColor(const math::vec4& color) { this->color = color; }
			inline void setTextCoord(const math::vec2& textCoord) { this->textCoord = textCoord; }

			friend Point operator+(const Point& left, const Point& right);
			friend Point operator-(const Point& left, const Point& right);
			Point& operator+=(const Point& right);
			Point& operator-=(const Point& right);

			friend Point operator+(const Point& left, const math::vec3& vector);
			friend Point operator-(const Point& left, const math::vec3& vector);
			Point& operator+=(const math::vec3& vector);
			Point& operator-=(const math::vec3& vector);

			inline double distTo(const Point &other) const { return this->pos.distTo(other.pos); }

		};

		class Polygon
		{
		private:
			std::vector<unsigned int> indecies;
		public:
			Polygon() {}
			Polygon(const std::vector<unsigned int>& indecies) : indecies(indecies) {}
			void set(const std::vector<unsigned int>& indecies) { this->indecies = indecies; }

			void addIndex(unsigned int index) { indecies.push_back(index); }
			const std::vector<unsigned int>& getIndecies() const { return indecies; }
			void clear() { indecies.clear(); }
		};

		class Mesh //: graphics::ISceneObject 
		{
		private:
			float* points = nullptr;
			unsigned int pointsCount;
			unsigned int* indecies = nullptr;
			unsigned int indeciesCount;
			math::vec3 center;
		public:
			Mesh() {}
			Mesh(const float *points, unsigned int pointsCount, const unsigned int* indecies, unsigned int indeciesCount, const math::vec3& position) {
				set(points, pointsCount, indecies, indeciesCount, position);
			}
			void set(const float *points, unsigned int pointsCount, const unsigned int* indecies, unsigned int indeciesCount, const math::vec3& position)
			{ 
				center = position;
				this->pointsCount = pointsCount;
				this->indeciesCount = indeciesCount;
				clearPoints();
				clearIndecies();
				this->points = new float[pointsCount*3];
				this->indecies = new unsigned int[indeciesCount];
				for (unsigned int id = 0; id < pointsCount*3; id++) 
				{
					this->points[id] = points[id];
				}
				for (unsigned int id = 0; id < indeciesCount; id++)
				{
					this->indecies[id] = indecies[id];
				}
			}
			~Mesh()
			{
				clearPoints();
				clearIndecies();
			}

			inline math::vec3 getPoint(unsigned int id) const { return math::vec3(points[id*3], points[id*3+1], points[id*3+2]); }
			inline unsigned int getIndex(unsigned int id) const { return indecies[id]; }

			inline unsigned int getCountPoints() const { return pointsCount; }
			inline unsigned int getCountIndecies() const { return indeciesCount; }

			inline float* const & getLocalPoints() const {
				return points;
			}
			inline unsigned int* const & getIndecies() const
			{
				return indecies;
			}

			inline void clearPoints()
			{ 
				if (points != nullptr)
				{
					delete[] points;
					points = nullptr;
				}
			}
			inline void clearIndecies()
			{ 
				if (indecies != nullptr)
				{
					delete[] indecies;
					indecies = nullptr;
				}
			}

			void applyMatrix(math::mat4 matr);

			inline math::vec3 getPosition() const { return center; }

			friend Mesh operator +(const Mesh& figure, const math::vec3& vec);
			friend Mesh operator -(const Mesh& figure, const math::vec3& vec);
			friend Mesh operator *(const Mesh& figure, const math::mat4& matrix);

			Mesh& operator +=(const math::vec3& vec);
			Mesh& operator -=(const math::vec3& vec);
			Mesh& operator *=(const math::mat4& matrix);
		};

	}
}