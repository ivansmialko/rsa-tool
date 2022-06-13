#include <iostream>
#include <numeric>
#include <cmath>
#include "Encryptor.h"
#include "Utilities.h"
#include "FileManager.h"
#include "KeyGenerator.h"
#include "CmdParser.h"
#include "Constants.h"

enum ARGUMENTS_INDEX
{
	ACTION = 1,
	KEY = 2,
	CONTENT_TYPE = 3,
	CONTENT_VALUE = 4,
	ARGUMENTS_AMOUNT
};

void debugPrintArguments(int in_argc, char ** in_argv)
{
	std::cout << "Arguments count: " << in_argc << std::endl;

	for (int i = 0; i < in_argc; i++)
	{
		std::cout << "Argument " << in_argv[i] << std::endl;
	}
}

void debugPrintNamedArguments(int in_argc, char ** in_argv)
{
	std::string action = in_argv[ACTION];
	std::string key = in_argv[KEY];
	std::string content_type = in_argv[CONTENT_TYPE];
	std::string content_value = in_argv[CONTENT_VALUE];

	std::cout << "Action to apply: " << action.c_str() << std::endl;
	std::cout << "Key: " << key.c_str() << std::endl;
	std::cout << "Content type: " << content_type.c_str() << std::endl;
	std::cout << "Content value: " << content_value.c_str() << std::endl;
}

bool checkArgumentsValidity(int in_argc, char ** in_argv)
{
	return in_argc != 1;
}

KeyPairData getKeyPairDataFromString(std::string in_input)
{
	KeyPairData keypair_data;

	std::vector<std::string> str_list = Utilities::split(in_input, ';');

	keypair_data.key = std::stoll(str_list[0]);
	keypair_data.public_m = std::stoll(str_list[1]);

	return keypair_data;
}

int main(int in_argc, char** in_argv)
{
	//KeyGenerator keygen;
	//KeySet generated = keygen.generateRandomKeys();
	//std::cout << generated.public_keypair.key << std::endl;
	//std::cout << generated.private_keypair.public_m << std::endl;

	if (!checkArgumentsValidity(in_argc, in_argv))
	{
		std::cout << "Arguments list not valid" << std::endl;
		return 0;
	}

	CmdParser cmd_options(in_argc, in_argv);

	if(!cmd_options.isOptionExist(OPTION_ACTION))
		return 0;

	std::string action = cmd_options.getOption(OPTION_ACTION);

	if (action == "generate")
	{

		if (!(cmd_options.isOptionExist(OPTION_GENERATE_KEYS_Q_VALUE) && cmd_options.isOptionExist(OPTION_GENERATE_KEYS_P_VALUE)))
		{
			std::cout << "No input p and q numbers. Please use external prime number generator, than pass one number to -kp parameter, and another to -kq" << std::endl;
			return 0;
		}

		KeyGenerator keygen;
		KeySet keyset = keygen.generateRandomKeys(atoi(cmd_options.getOption(OPTION_GENERATE_KEYS_P_VALUE).c_str()), atoi(cmd_options.getOption(OPTION_GENERATE_KEYS_Q_VALUE).c_str()));

		std::cout << "Your public key: {" << keyset.public_keypair.key << ";" << keyset.public_keypair.public_m << "}" << std::endl;
		std::cout << "Your private key: {" << keyset.private_keypair.key << ";" << keyset.private_keypair.public_m << "}" << std::endl;

		std::cout << "Warning:\n1. DO NOT DISTRIBUTE PRIVATE KEY!!!.\n2. DO NOT DISTRIBUTE Q NUMBER. DESTROY IT!!!" << std::endl;
		std::cout << "Keys successfully generated" << std::endl;
		system("pause");
		return 0;
	}

	//Parse keys
	std::string keypair_string;
	if (cmd_options.isOptionExist(OPTION_KEY))
	{
		keypair_string = cmd_options.getOption(OPTION_KEY);
	}
	else if (cmd_options.isOptionExist(OPTION_KEY_FILE))
	{
		std::string filename = cmd_options.getOption(OPTION_KEY_FILE);
		std::vector<char> key_data = FileManager::readFie(filename);
		keypair_string = std::string(key_data.begin(), key_data.end());
	}

	KeyPairData keypair_input = getKeyPairDataFromString(keypair_string);

	//Parse input
	if (!cmd_options.isOptionExist(OPTION_KEY) && !cmd_options.isOptionExist(OPTION_KEY_FILE))
		return 0;

	if (!cmd_options.isOptionExist(OPTION_INPUT) && !cmd_options.isOptionExist(OPTION_INPUT_FILE))
		return 0;

	std::vector<char> working_data;
	if (cmd_options.isOptionExist(OPTION_INPUT))
	{
		std::string input_data = cmd_options.getOption(OPTION_INPUT);
		working_data = std::vector<char>(input_data.begin(), input_data.end());
	}
	else if (cmd_options.isOptionExist(OPTION_INPUT_FILE))
	{
		std::string file_name = cmd_options.getOption(OPTION_INPUT_FILE);
		working_data = FileManager::readFie(file_name);
	}

	//Parse input and do actions
	std::vector<char> processed_data;
	if (action == "encrypt")
	{
		processed_data = Encryptor::process(working_data, keypair_input, true);
	}
	if (action == "decrypt")
	{
		processed_data = Encryptor::process(working_data, keypair_input, false);
	}

	//Write result to file if needed
	if (cmd_options.isOptionExist(OPTION_OUTPUT_FILE))
	{
		FileManager::writeFile(processed_data, cmd_options.getOption(OPTION_OUTPUT_FILE));
	} 

	std::cout << "Processed data:\n" << std::string(processed_data.begin(), processed_data.end());

	return 0;
}