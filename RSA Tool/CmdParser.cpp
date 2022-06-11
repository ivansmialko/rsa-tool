#include "CmdParser.h"

std::string CmdParser::getCmdOption(const std::string in_option_name)
{
	char ** itr = std::find(_argv, _argv + _argc, in_option_name);
	if (itr != _argv + _argc && ++itr != _argv + _argc)
	{
		return std::string(*itr);
	}

	return std::string();
}

bool CmdParser::getIsCmdOptionExists(const std::string in_option_name)
{
	return (std::find(_argv, _argv + _argc, in_option_name) != _argv + _argc);
}

CmdParser::CmdParser(int in_argc, char** in_argv)
{
	_argc = in_argc;
	_argv = in_argv;
}

std::string CmdParser::getOption(const std::string& option_name)
{
	if (_cmd_options.find(option_name) == _cmd_options.end())
	{
		if (!getIsCmdOptionExists(option_name))
			return std::string();

		_cmd_options[option_name] = getCmdOption(option_name);
	}

	return _cmd_options[option_name];
}

bool CmdParser::isOptionExist(const std::string& option_name)
{
	if (_cmd_options.find(option_name) == _cmd_options.end())
	{
		if (!getIsCmdOptionExists(option_name))
			return false;

		_cmd_options[option_name] = getCmdOption(option_name);
	}

	return true;
}
