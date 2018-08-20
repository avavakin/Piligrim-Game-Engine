#pragma once

#include <string>

#include "../utils/fileutils.h"

#include "data/KeyRole.h"

class Config
{
public:
	Config();
	Config(const std::string& path);

	int getKeyCode(KeyRole key) const;
	void load(const std::string& path);

	static char invalidConfigMessage[];

private:
	int bindings_[KeyRole::MaxKeyRole];

private:
	KeyRole parseKeyRole(const std::string& word);
	int parseKeyCode(const std::string& word);
};