#pragma once
#include <utility>
#include "KeySet.h"

class KeyGenerator
{
public:
	static KeySet generateRandomKeys(long int in_p, long int in_q);
};