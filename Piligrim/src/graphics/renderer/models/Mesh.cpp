#include "Mesh.h"
namespace piligrim {
	namespace graphics {



		void Mesh::set(const std::vector<VertexUnion>& verticies)
		{
			verticies_ = verticies;
		}



		void Mesh::set(const std::vector<Vertex>& verticies)
		{			
			unsigned int vertSize = verticies.size();
			verticies_.resize(vertSize);

			for (unsigned int vertId = 0; vertId < vertSize; vertId++) {
				verticies_[vertId].vertex = verticies[vertId];
			}
		}



		void Mesh::set(const std::vector<float>& verticies)
		{
			unsigned int vertSize = verticies.size() / VERTEX_FLOATS;
			verticies_.resize(vertSize);

			unsigned int offset;
			for (unsigned int vertId = 0; vertId < vertSize; vertId++) {
				offset = vertId * VERTEX_FLOATS;
				for (unsigned short floatId = 0; floatId < VERTEX_FLOATS; floatId++) {
					verticies_[vertId].floats[floatId] = verticies[offset + floatId];
				}
			}
		}



		void Mesh::set(const std::vector<unsigned int>& indicies)
		{
			indicies_ = indicies;
		}



		void Mesh::set(const std::vector<Texture> textures)
		{
			textures_ = textures;
		}



		Vertex Mesh::getVertex(unsigned int id) const
		{
			return verticies_[id].vertex;
		}



		unsigned int Mesh::getVerticiesCount() const
		{
			return verticies_.size() / VERTEX_FLOATS;
		}



		unsigned int Mesh::getIndiciesCount() const
		{
			return indicies_.size();
		}



		std::vector<unsigned int> const & Mesh::getIndicies() const
		{
			return indicies_;
		}



		void Mesh::draw(Shader& shader)
		{
			unsigned short texSize = textures_.size();

			for (unsigned int texId = 0; texId < texSize; texId++) {
				textures_[texId].bind();
			}
			glActiveTexture(GL_TEXTURE0);

			vao.bind();
			ibo.bind();

			glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, 0);

			ibo.unbind();
			vao.unbind();

			for (auto& texture: textures_) {
				texture.unbind();
			}
		}



		void Mesh::init(MeshConfig config)
		{
			config_ = config;
			ibo.set(indicies_.data(), indicies_.size());

			vao.setBuffer(new Buffer(&verticies_.data()->floats[0], verticies_.size() * VERTEX_FLOATS * sizeof(float)));

			vao.addBufferAttributes(0, 3, VERTEX_FLOATS * sizeof(float), 0);
			if (config & MeshConfig::NORMALS == MeshConfig::NORMALS) {
				vao.addBufferAttributes(1, 3, VERTEX_FLOATS * sizeof(float), 3 * sizeof(float));
			}
			if (config & MeshConfig::TEXCOORDS == MeshConfig::TEXCOORDS) {
				vao.addBufferAttributes(2, 2, VERTEX_FLOATS * sizeof(float), 6 * sizeof(float));
			}
		}



	}
}