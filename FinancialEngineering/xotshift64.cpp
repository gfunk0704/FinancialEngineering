#include <xorshift64.h>

namespace FinancialEngineering
{
	XorshiftStar64::XorshiftStar64(BigNatural seed) :
		Rng64Bits(seed),
		_s(seed)
	{}

	XorshiftStar64::XorshiftStar64():
		XorshiftStar64(GlobalVariable::get_seed())
	{}

	XorshiroStarStar256::XorshiroStarStar256(BigNatural seed) :
		Rng64Bits(seed)
	{
		reset();
	}

	XorshiroStarStar256::XorshiroStarStar256() :
		XorshiroStarStar256(GlobalVariable::get_seed())
	{}

	void XorshiroStarStar256::reset()
	{
		XorshiftStar64 rng(_seed);
		for (unsigned i = 0; i < 4; i++)
		{
			_s[i] = rng.next();
		}
	}

	BigNatural XorshiroStarStar256::next()
	{
		uint64_t const result = rol64(_s[1] * 5, 7) * 9;
		uint64_t const t = _s[1] << 17;

		_s[2] ^= _s[0];
		_s[3] ^= _s[1];
		_s[1] ^= _s[2];
		_s[0] ^= _s[3];

		_s[2] ^= t;
		_s[3] = rol64(_s[3], 45);

		return result;
	}
}