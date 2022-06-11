#pragma once
#include <vector>

class FileManager
{
public:
	static const std::vector<char> readFie(std::string in_file_name);
	static const void writeFile(const std::vector<char>& in_data, std::string in_file_name);
};