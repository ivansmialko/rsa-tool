#pragma once
#include <string>
#include <vector>
#include "KeyPairData.h"

class Encryptor
{
private:
	static uint8_t getChunkSize(KeyPairData in_key);

public:
	static std::vector<char> process(std::vector<char>& in_data, KeyPairData in_keys, bool in_is_encrypt);
};