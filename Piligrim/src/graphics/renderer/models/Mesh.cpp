#include "Mesh.h"
namespace piligrim {
	namespace graphics {
		

		Mesh::Mesh()
		{
		}

		Mesh::Mesh(const std::vector<Vertex>& verticies, const std::vector<unsigned int>& indicies)
		{
			set(verticies, indicies);
		}

		void Mesh::set(const std::vector<Vertex>& verticies)
		{
			verticies_ = verticies;
		}

		void Mesh::set(const std::vector<unsigned int>& indicies)
		{
			indicies_ = indicies;
		}

		void Mesh::set(const std::vector<Vertex>& verticies, const std::vector<unsigned int>& indicies)
		{
			verticies_ = verticies;
			indicies_ = indicies;
		}

		Vertex Mesh::getVertex(unsigned int id) const
		{
			return verticies_[id];
		}

		unsigned int Mesh::getVerticiesCount() const
		{
			return verticies_.size();
		}

		unsigned int Mesh::getIndiciesCount() const
		{
			return indicies_.size();
		}

		std::vector<Vertex> const & Mesh::getVerticies() const
		{
			return verticies_;
		}

		std::vector<unsigned int> const & Mesh::getIndicies() const
		{
			return indicies_;
		}
		
	}
}