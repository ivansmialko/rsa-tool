#include "KeyGenerator.h"
#include "Utilities.h"
#include "Constants.h"

KeySet KeyGenerator::generateRandomKeys()
{
	long int p = 3557;
	long int q = 2579;

	long int public_key = p * q;

	long int phi = Utilities::etf(public_key);
	int private_key = Utilities::modi(PUBLIC_E, phi);

	KeyPairData public_key_pair;
	public_key_pair.key = PUBLIC_E;
	public_key_pair.public_m = public_key;

	KeyPairData private_key_pair;
	private_key_pair.key = p;
	private_key_pair.public_m = public_key;

	KeySet key_set;
	key_set.public_keypair = public_key_pair;
	key_set.private_keypair = private_key_pair;

	return key_set;
}
