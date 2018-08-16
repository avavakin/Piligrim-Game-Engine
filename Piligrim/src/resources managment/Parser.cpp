#include "Parser.h"

Mesh Parser::parseMesh(const std::string & path)
{
	std::ifstream file(path);

	if (!file.is_open()) {
		throw std::invalid_argument("Path to .obj file is invalide");
	}
	Mesh result;

	result.config_ = MeshConfig::NOTHING;

	char mode[64];
	char symbol = ' ';

	std::vector<vec3> positions;
	std::vector<vec2> texCoords;
	std::vector<vec3> normals;

	vec3 tempPosition;
	vec2 tempTexCoord;
	vec3 tempNormal;

	enum FaceMode : __int8{
		VERT_ID,
		TEX_ID,
		NORM_ID
	} faceMode;

	int idTemp = 0;

	VertexUnion vertexUnion;
	unsigned int indexId = 0;
	while (!file.eof()) {
		file >> mode;
		if (mode[0] == 'v' && mode[1] == '\0') {
			file >> tempPosition.x >> tempPosition.y >> tempPosition.z;
			positions.push_back(tempPosition);
			// TODO: send warning about 'w' coordinate
			while (file.get() != '\n');
		}
		else if (mode[0] == 'v' && mode[1] == 't') {
			file >> tempTexCoord.x >> tempTexCoord.y;
			texCoords.push_back(tempTexCoord);
			// TODO: send warning about 'w' coordinate
			while (file.get() != '\n');

		}
		else if (mode[0] == 'v' && mode[1] == 'n') {
			file >> tempNormal.x >> tempNormal.y >> tempNormal.z;
			normals.push_back(tempNormal);
		}
		else if (mode[0] == 'f' && mode[1] == '\0') {
			do {
				symbol = file.get();
			} while (symbol == ' ');
			while (symbol != '\n' && !file.eof()) {
				faceMode = VERT_ID;
				idTemp = 0;
				while (symbol != ' ' && symbol != '\n' &&  !file.eof()) {
					if (symbol != '/') {
						idTemp *= 10;
						idTemp += static_cast<int>(symbol - '0');
					}
					else {
						switch (faceMode) {
						case VERT_ID:
							vertexUnion.vertex.position = positions[idTemp - 1];
							faceMode = TEX_ID;
							break;
						case TEX_ID:
							vertexUnion.vertex.texCoords = texCoords[idTemp - 1];
							result.config_ = static_cast<MeshConfig>(result.config_ | MeshConfig::TEXCOORDS);
							faceMode = NORM_ID;
							break;
						}
						idTemp = 0;
					}
					symbol = file.get();
				}
				if (faceMode == NORM_ID) {
					vertexUnion.vertex.normal = normals[idTemp - 1];
					result.config_ = static_cast<MeshConfig>(result.config_ | MeshConfig::NORMALS);
				}
				idTemp = 0;
				result.verticies_.push_back(vertexUnion);
				result.indicies_.push_back(indexId++);
				while (symbol == ' ' && symbol != '\n' && !file.eof()) {
					symbol = file.get();
				}
			}
		}
		else {
			while (file.get() != '\n' && !file.eof())
				;
		}
	}

	file.close();
	return result;
}