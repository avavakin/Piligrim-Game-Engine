#pragma once
#include <string>
#include <list>
#include <regex>

#include "../utils/FileUtils.h"

#include "../graphics/renderer/models/Mesh.h"
#include "../graphics/renderer/models/Material.h"

namespace piligrim {

	class Parser
	{
	public:
		Parser() = delete;
		static graphics::Mesh parseMesh(const std::string& path);
		//static graphics::Mesh parseMaterial(const std::string& path);
	private:
		static void parseVertexInfo(const std::string& str, unsigned int& posId, unsigned int& texId, unsigned int& normId);
	private:
		static const char vertexRe[];
		static const char normalRe[];
		static const char textureRe[];
		static const char faceRe[];
		static const char indexRe[];
	};

}
