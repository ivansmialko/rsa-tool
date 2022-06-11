#pragma once
#include<climits>
#include <vector>
#include <string>

class Utilities
{
public:
	//Euler's totient function
	static long int etf(long int in_number);

	//Extended Euclidean algorithm
	static int eea(int in_a, int in_b, int* in_x, int* in_y);

	//Module inverse of a by module of m
	static int modi(int in_a, int in_m);

	//Greatest common divisor
	static long unsigned int gcd(long unsigned int in_n1, long unsigned int in_n2);

	//Modular exponentiation
	static unsigned long long int binpow(unsigned long long int a, unsigned long long int e, unsigned long long int mod = LLONG_MAX);

	//Simple square function
	static unsigned long long int square(unsigned long long int in_a);

	//Divide data to blocks of another size
	static std::vector<unsigned long long> resize(const std::vector<unsigned long long>& in_data, uint8_t in_size, uint8_t in_out_size);

	//Split string by separator
	static std::vector<std::string> split(const std::string & in_string, char in_separator);


};