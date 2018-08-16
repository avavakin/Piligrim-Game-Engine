#pragma once
#include <vector>

#include "../../../math/math.h"
#include "../../buffers/buffers.h"
#include "../../shader.h"

#include "IDrawable.h"
#include "Vertex.h"
#include "Texture.h"

enum MeshConfig : bool {
	NOTHING = 0b00,
	NORMALS = 0b01,
	TEXCOORDS = 0b10,
	ALL = 0b11
};

class Mesh : IDrawable
{
public:
	void setVerticies(const std::vector<VertexUnion>& verticies);
	void setVerticies(const std::vector<Vertex>& verticies);
	void setVerticies(const std::vector<float>& verticies);
	void setIndicies(const std::vector<unsigned int>& indicies);

	void addTexture(Texture* texture);
	void addVertex(const Vertex& vertex);
	void addPolygon(unsigned int first, unsigned int second, unsigned int third);

	Vertex getVertex(unsigned int id) const;

	unsigned int getVerticiesCount() const;
	unsigned int getIndiciesCount() const;

	std::vector<unsigned int> const & getIndicies() const;

	void setShader(Shader* shader);
	void setConfig(MeshConfig config);
	void setDrawMode(GLenum drawMode);

	void draw();
	void init();
	void deleteBuffer() const;

protected:
	std::vector<VertexUnion> verticies_;
	std::vector<unsigned int> indicies_;
	std::vector<Texture*> textures_;
	MeshConfig config_;
	GLenum drawMode_;
	Shader* shader_;

private:
	VertexArray vao;
	IndexBuffer ibo;
};