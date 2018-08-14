#include "fileutils.h"


namespace piligrim {



	std::string FileUtils::readFile(const std::string & filepath)
	{
		FILE * file = fopen(filepath.c_str(), "rt");

		if (file == nullptr) {
			throw std::invalid_argument("Invalid path to file!");
		}

		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char *data = new char[length + 1];

		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, sizeof(char), length, file);
		fclose(file);

		std::string result(data);
		delete[] data;

		return result;
	}



	void FileUtils::readTwoDividedWords(std::ifstream & file, std::string & first, std::string & second)
	{
		file >> first;
		file >> second >> second;
	}



	bool FileUtils::getNextLine(std::ifstream & file, std::string & line)
	{
		if (file.eof()) {
			return false;
		}

		std::getline(file, line);

		return true;
	}



}