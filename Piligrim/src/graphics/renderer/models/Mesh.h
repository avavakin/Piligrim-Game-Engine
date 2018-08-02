#pragma once
#include "../../../math/math.h"
#include "../../buffers/vertexarray.h"
#include "../../buffers/buffer.h"
#include "Vertex.h"
#include <vector>
namespace piligrim {
	namespace graphics {

		class Mesh 
		{
		public:
			Mesh();
			Mesh(const std::vector<Vertex>& verticies, const std::vector<unsigned int>& indicies);

			void set(const std::vector<Vertex>& verticies);
			void set(const std::vector<unsigned int>& indicies);
			void set(const std::vector<Vertex>& verticies, const std::vector<unsigned int>& indicies);

			Vertex getVertex(unsigned int id) const;

			unsigned int getVerticiesCount() const;
			unsigned int getIndiciesCount() const;

			std::vector<Vertex> const & getVerticies() const;
			std::vector<unsigned int> const & getIndicies() const;
		private:
			std::vector<Vertex> verticies_;
			std::vector<unsigned int> indicies_;
		};

	}
}