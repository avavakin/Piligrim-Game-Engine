#include "Parser.h"




const char Parser::vertexRe[] = "(?:v)(\\s+-?[0-9]+\\.[0-9]+)(\\s+-?[0-9]+\\.[0-9]+)(\\s+-?[0-9]+\\.[0-9]+)(\\s+-?[0-9]+\\.[0-9]+)?";
const char Parser::normalRe[] = "(?:vn)(\\s+-?[0-9]+\\.[0-9]+)(\\s+-?[0-9]+\\.[0-9]+)(\\s+-?[0-9]+\\.[0-9]+)";
const char Parser::textureRe[] = "(?:vt)(\\s+-?[0-9]+\\.[0-9]+)(\\s+-?[0-9]+\\.[0-9]+)(\\s+-?[0-9]+\\.[0-9]+)?";
const char Parser::faceRe[] = "(?:f)(\\s+[0-9]+\/?(?:[0-9]+)?\/?(?:[0-9]+)?)(\\s+[0-9]+\/?(?:[0-9]+)?\/?(?:[0-9]+)?)(\\s+[0-9]+\/?(?:[0-9]+)?\/?(?:[0-9]+)?)";
const char Parser::indexRe[] = "(?:\\s)?([0-9]+)(?:\/)?([0-9]+)?(?:\/?)([0-9]+)?";

Mesh Parser::parseMesh(const std::string & path)
{

	std::regex reVertex(vertexRe);
	std::regex reNormal(normalRe);
	std::regex reTexture(textureRe);
	std::regex reFace(faceRe);

	std::ifstream file(path);

	if (!file.is_open()) {
		throw std::invalid_argument("Path to .obj file is invalide");
	}

	std::vector<vec3> positions;
	std::vector<vec3> normals;
	std::vector<vec2> textures;

	std::vector<Vertex> verticies;

	std::smatch resultRe;
	std::string line;
	unsigned int faceId = 0;

	MeshConfig config = MeshConfig::NOTHING;

	Mesh result;
	Vertex vertex;
	for (unsigned int lineNo = 1; FileUtils::getNextLine(file, line); lineNo++) {
		if (line.size() < 2) {
			continue;
		}

		if (line[0] == 'v' && line[1] == ' ') {
			if (std::regex_match(line, resultRe, reVertex)) {
				positions.push_back(
					vec3(
						atof(resultRe[1].str().c_str()),
						atof(resultRe[2].str().c_str()),
						atof(resultRe[3].str().c_str())
					)
				);
			}
			else {
				throw std::invalid_argument("Possition line " + std::to_string(lineNo) + " is invalid.");
			}
		}
		else if (line[0] == 'v' && line[1] == 'n') {
			if (std::regex_match(line, resultRe, reNormal)) {
				config = static_cast<MeshConfig>(config | MeshConfig::NORMALS);
				normals.push_back(
					vec3(
						atof(resultRe[1].str().c_str()),
						atof(resultRe[2].str().c_str()),
						atof(resultRe[3].str().c_str())
					)
				);
			}
			else {
				throw std::invalid_argument("Normal line " + std::to_string(lineNo) + " is invalid.");
			}
		}
		else if (line[0] == 'v' && line[1] == 't') {
			if (std::regex_match(line, resultRe, reTexture)) {
				config = static_cast<MeshConfig>(config | MeshConfig::TEXCOORDS);
				textures.push_back(
					vec2(
						atof(resultRe[1].str().c_str()),
						atof(resultRe[2].str().c_str())
					)
				);
			}
			else {
				throw std::invalid_argument("Texture line " + std::to_string(lineNo) + " is invalid.");
			}
		}
		else if (line[0] == 'f' && line[1] == ' ') {
			if (std::regex_match(line, resultRe, reFace)) {
				unsigned int posId, texId, normId;
				try {
					for (unsigned __int8 vertId = 1; vertId <= 3; vertId++) {
						parseVertexInfo(resultRe[vertId].str(), posId, texId, normId);
						vertex.position = positions[posId];

						if (config & MeshConfig::TEXCOORDS) {
							vertex.texCoords = textures[texId];
						}
						else {
							vertex.texCoords = vec2(0.0f, 0.0f);
						}

						if (config & MeshConfig::NORMALS) {
							vertex.normal = normals[normId];
						}
						else {
							vertex.normal = vec3(0.0f, 0.0f, 0.0f);
						}

						verticies.push_back(vertex);
					}
					result.addPolygon(faceId * 3, faceId * 3 + 1, faceId * 3 + 2);
					faceId++;
				}
				catch (std::invalid_argument e) {
					throw std::invalid_argument("Face line " + std::to_string(lineNo) + " is invalid. : " + e.what());
				}

			}
			else {
				throw std::invalid_argument("Face line " + std::to_string(lineNo) + " is invalid.");
			}
		}
	}

	result.setVerticies(verticies);
	result.setConfig(config);
	return result;
}



void Parser::parseVertexInfo(const std::string & str, unsigned int & posId, unsigned int & texId, unsigned int & normId)
{
	std::regex re(indexRe);
	std::smatch resultRe;
	if (std::regex_match(str, resultRe, re)) {
		std::string strPos = resultRe[1].str();
		std::string strTex = resultRe[2].str();
		std::string strNorm = resultRe[3].str();

		posId = atoi(strPos.c_str()) - 1;
		texId = strTex.empty() ? 0 : atoi(strTex.c_str()) - 1;
		normId = strNorm.empty() ? 0 : atoi(strNorm.c_str()) - 1;
	}
	else {
		throw std::invalid_argument("Invalid vertex data");
	}
}