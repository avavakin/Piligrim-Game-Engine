#pragma once
#include <string>
#include <list>
#include <regex>

#include "../utils/FileUtils.h"

#include "../graphics/renderer/models/Mesh.h"
#include "../graphics/renderer/models/Material.h"



class Parser
{
public:
	Parser() = delete;
	static Mesh parseMesh(const std::string& path);
	//static Mesh parseMaterial(const std::string& path);
};