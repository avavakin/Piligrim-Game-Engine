#pragma once
#include <vector>

#include "../../../math/math.h"
#include "../../buffers/buffers.h"
#include "../../shader.h"

#include "IDrawable.h"
#include "Vertex.h"
#include "Texture.h"

namespace piligrim {
	namespace graphics {

		class Mesh : public IDrawable
		{
		public:
			Mesh();

			void set(const std::vector<VertexUnion>& verticies);
			void set(const std::vector<Vertex>& verticies);
			void set(const std::vector<float>& verticies);
			void set(const std::vector<unsigned int>& indicies);
			void set(const std::vector<Texture> textures);

			Vertex getVertex(unsigned int id) const;

			unsigned int getVerticiesCount() const;
			unsigned int getIndiciesCount() const;

			std::vector<unsigned int> const & getIndicies() const;

			void draw(Shader &shader);
			void init();

		private:
			std::vector<VertexUnion> verticies_;
			std::vector<unsigned int> indicies_;
			std::vector<Texture> textures_;

			VertexArray vao;
			IndexBuffer ibo;
		};

	}
}