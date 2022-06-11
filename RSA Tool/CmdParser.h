#pragma once
#include <map>
#include <string>

class CmdParser
{
private:
	int _argc;
	char ** _argv;

	std::map<std::string, std::string> _cmd_options;

	//Get option data from cmd parameters
	std::string getCmdOption(const std::string in_option_name);

	//Check if option exists in cmd parameters
	bool getIsCmdOptionExists(const std::string in_option_name);

public:
	CmdParser(int in_argc, char** in_argv);

	std::string getOption(const std::string& option_name);
	bool isOptionExist(const std::string& option_name);
};