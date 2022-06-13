#include "KeyGenerator.h"
#include "Utilities.h"
#include "Constants.h"

KeySet KeyGenerator::generateRandomKeys(long int in_p, long int in_q)
{
	long int n = in_p * in_q;

	long int phi = Utilities::etf(n);
	long long int private_key = Utilities::modi(PUBLIC_E, phi);

	KeyPairData public_key_pair;
	public_key_pair.key = PUBLIC_E;
	public_key_pair.public_m = n;

	KeyPairData private_key_pair;
	private_key_pair.key = private_key;
	private_key_pair.public_m = n;

	KeySet key_set;
	key_set.public_keypair = public_key_pair;
	key_set.private_keypair = private_key_pair;

	return key_set;
}
