#include "Utilities.h"
#include <stdint.h>
#include <cmath>
#include <random>
#include <iostream>

//Source code: https://uk.wikipedia.org/wiki/%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D1%96%D1%8F_%D0%95%D0%B9%D0%BB%D0%B5%D1%80%D0%B0
long int Utilities::etf(long int in_number)
{
	int ret = 1;
	for (int i = 2; i * i <= in_number; ++i) {
		int p = 1;
		while (in_number % i == 0) {
			p *= i;
			in_number /= i;
		}
		if ((p /= i) >= 1) ret *= p * (i - 1);
	}
	return --in_number ? in_number * ret : ret;
}
//Source code: https://www.geeksforgeeks.org/euclidean-algorithms-basic-and-extended/
long long int Utilities::eea(long long int in_a, long long int in_b, long long int* in_x, long long int* in_y)
{
	// Base Case
	if (in_a == 0)
	{
		*in_x = 0, *in_y = 1;
		return in_b;
	}

	// To store results of recursive call
	long long int x1, y1;
	long long int gcd = eea(in_b % in_a, in_a, &x1, &y1);

	// Update x and y using results of recursive
	// call
	*in_x = y1 - (in_b / in_a) * x1;
	*in_y = x1;

	return gcd;
}

long long int Utilities::modi(long long int in_a, long long int in_m)
{
	long long int x, y;
	eea(in_a, in_m, &x, &y);
	
	x = (x % in_m + in_m) % in_m;
	return x;
}

long unsigned int Utilities::gcd(long unsigned int in_n1, long unsigned int in_n2)
{
	return (in_n2 == 0) ? in_n1 : gcd(in_n2, in_n1 % in_n2);
}

unsigned long long int Utilities::square(unsigned long long int in_a)
{
	return in_a * in_a;
}

std::vector<unsigned long long> Utilities::resize(const std::vector<unsigned long long>& in_data, uint8_t in_size, uint8_t in_out_size)
{
	std::vector<unsigned long long> result;
	uint8_t done = 0;
	uint64_t curr = 0;

	for (auto byte : in_data)
	{
		for (uint8_t i = 0; i < in_size; i++)
		{
			curr = (curr << 1U) + (((uint64_t)byte & (1U << (uint64_t)(in_size - 1 - i))) != 0);
			done++;

			if (done == in_out_size)
			{
				done = 0;
				result.push_back(curr);
				curr = 0;
			}
		}
	}

	if (done != 0)
	{
		result.push_back(curr << (uint64_t)(in_out_size - done));
	}

	return result;
}

std::vector<std::string> Utilities::split(const std::string & in_string, char in_separator)
{
	std::vector<std::string> output;

	std::string::size_type prev_pos = 0, pos = 0;

	while ((pos = in_string.find(in_separator, pos)) != std::string::npos)
	{
		std::string substring(in_string.substr(prev_pos, pos - prev_pos));

		output.push_back(substring);

		prev_pos = ++pos;
	}

	output.push_back(in_string.substr(prev_pos, pos - prev_pos));

	return output;
}

unsigned long long Utilities::getRandomNumber(long unsigned int in_min, long unsigned int in_max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(in_min, in_max);

	return distr(gen);
}

unsigned long long int Utilities::binpow(unsigned long long int a, unsigned long long int e, unsigned long long int mod /*= LLONG_MAX*/)
{
	return e == 0 ? 1 : (e & 1U ? a * binpow(a, e - 1, mod) % mod : square(binpow(a, e / 2, mod)) % mod);
}

