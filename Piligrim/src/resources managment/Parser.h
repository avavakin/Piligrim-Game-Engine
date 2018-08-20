#pragma once
#include <string>

#include "../utils/FileUtils.h"

#include "../graphics/renderer/meshes/Mesh.h"
#include "../graphics/renderer/shader/Material.h"



class Parser
{
public:
	Parser() = delete;
	static Mesh parseMesh(const std::string& path);
	//static Mesh parseMaterial(const std::string& path);
};