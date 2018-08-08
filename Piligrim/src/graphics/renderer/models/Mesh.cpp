#include "Mesh.h"
namespace piligrim {
	namespace graphics {
		

		Mesh::Mesh()
		{
		}

		void Mesh::set(const std::vector<VertexUnion>& verticies)
		{
			verticies_ = verticies;
		}

		void Mesh::set(const std::vector<Vertex>& verticies)
		{			
			unsigned int verticiesSize = verticies.size();
			verticies_.resize(verticiesSize);

			for (unsigned int id = 0; id < verticiesSize; id++) {
				verticies_[id].vertex = verticies[id];
			}
		}

		void Mesh::set(const std::vector<float>& verticies)
		{
			unsigned int verticiesSize = verticies.size() / VERTEX_FLOATS;
			verticies_.resize(verticiesSize);

			for (unsigned int id = 0; id < verticiesSize; id++) {
				verticies_[id].floats[0] = verticies[id * VERTEX_FLOATS];
				verticies_[id].floats[1] = verticies[id * VERTEX_FLOATS + 1];
				verticies_[id].floats[2] = verticies[id * VERTEX_FLOATS + 2];


				verticies_[id].floats[3] = verticies[id * VERTEX_FLOATS + 3];
				verticies_[id].floats[4] = verticies[id * VERTEX_FLOATS + 4];
				verticies_[id].floats[5] = verticies[id * VERTEX_FLOATS + 5];


				verticies_[id].floats[6] = verticies[id * VERTEX_FLOATS + 6];
				verticies_[id].floats[7] = verticies[id * VERTEX_FLOATS + 7];
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
			/*
			shader.enable();
			shader.setUniform("u_vw_matrix", cam.getMatrix());
			
			lightCenter = vec3(
			cos(glfwGetTime())*lightRad,
			cos(glfwGetTime())*lightRad,
			sin(glfwGetTime())*lightRad
			);
			
			shader.setUniform("u_light.position", lightCenter);
			shader.setUniform("u_cam_pos", cam.getPosition());
			shader.setUniform("u_ml_matrix", mat4::translation(figureCenter));
			*/
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
			/*
			shaderMesh.disable();
			*/
			
		}

		void Mesh::init()
		{
			ibo.set(indicies_.data(), indicies_.size());

			vao.setBuffer(new Buffer(&verticies_.data()->floats[0], verticies_.size() * VERTEX_FLOATS * sizeof(float)));
			vao.addBufferAttributes(0, 3, VERTEX_FLOATS * sizeof(float), 0); // positions
			vao.addBufferAttributes(1, 3, VERTEX_FLOATS * sizeof(float), 3 * sizeof(float)); // normals
			vao.addBufferAttributes(2, 2, VERTEX_FLOATS * sizeof(float), 6 * sizeof(float)); // texture coords
		}
		
	}
}