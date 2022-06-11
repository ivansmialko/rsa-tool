#include "Encryptor.h"
#include "Utilities.h"
#include <intrin.h>

uint8_t Encryptor::getChunkSize(KeyPairData in_key)
{
	return 32 - __lzcnt(in_key.public_m);
}

std::vector<char> Encryptor::process(std::vector<char>& in_data, KeyPairData in_keys, bool in_is_encrypt)
{
	std::vector<unsigned long long> data_64(in_data.size());
	for (unsigned int i = 0; i < in_data.size(); i++)
	{
		data_64[i] = static_cast<unsigned long long>(in_data[i]);
	}

	std::vector<unsigned long long> resized_data = Utilities::resize(data_64, 8, getChunkSize(in_keys) - in_is_encrypt);
	std::vector<unsigned long long> processed_data(resized_data.size());
	for (unsigned int i = 0; i < resized_data.size(); i++)
	{
		processed_data[i] = Utilities::binpow(resized_data[i], in_keys.key, in_keys.public_m);
	}

	std::vector<unsigned long long> result_64 = Utilities::resize(resized_data, getChunkSize(in_keys) - !in_is_encrypt, 8);
	std::vector<char> result_8(result_64.size());
	for (unsigned int i = 0; i < result_8.size(); i++)
	{
		result_8[i] = static_cast<char>(result_64[i]);
	}

	return result_8;
}
