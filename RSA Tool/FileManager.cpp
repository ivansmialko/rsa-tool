#include "FileManager.h"
#include <iostream>
#include <fstream>

const std::vector<char> FileManager::readFie(std::string in_file_name)
{
	std::ifstream file_input(in_file_name);
	if (!file_input)
		return std::vector<char>();

	file_input.seekg(0, std::ios::end);
	size_t length = file_input.tellg();
	char* bytes = new char[length];

	file_input.seekg(0, std::ios::beg);
	file_input.read(bytes, length);
	file_input.close();

	std::vector<char> data(length);
	for (unsigned int i = 0; i < length; i++)
	{
		data[i] = bytes[i];
	}

	delete[] bytes;
	return data;
}

const void FileManager::writeFile(const std::vector<char>& in_data, std::string in_file_name)
{
	std::ofstream output_file(in_file_name);
	char * buffer = new char[in_data.size()];

	for (unsigned int i = 0; i < in_data.size(); i++)
	{
		buffer[i] = in_data[i];
	}

	output_file.write(buffer, in_data.size());
	output_file.close();
}
