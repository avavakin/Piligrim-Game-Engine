#pragma once
#include <string>
#include <fstream>

class FileUtils
{
public:
	FileUtils() = delete;

	static std::string readFile(const std::string& filepath);

	static void readTwoDividedWords(std::ifstream& file, std::string& first, std::string& second);

	static bool getNextLine(std::ifstream& file, std::string& line);
};