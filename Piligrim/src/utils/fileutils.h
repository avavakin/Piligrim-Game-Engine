#pragma once
#include <string>

namespace piligrim {

	class FileUtils
	{
	public:
		static std::string readFile(std::string filepath)
		{
			FILE * file = fopen(filepath.c_str(), "rt");
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
	};

}