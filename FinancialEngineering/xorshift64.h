#pragma once

#include <rng_64bits.h>

namespace FinancialEngineering
{

	class XorshiftStar64 : public Rng64Bits
	{
	public:
		XorshiftStar64(BigNatural);
		XorshiftStar64();
		void reset() override;
		BigNatural next() override;
	private:
		BigNatural _s;
	};

	inline void XorshiftStar64::reset()
	{
		_s = _seed;
	}

	inline BigNatural XorshiftStar64::next()
	{
		_s ^= _s >> 12; // a
		_s ^= _s << 25; // b
		_s ^= _s >> 27; // c
		return _s * UINT64_C(0x2545F4914F6CDD1D);
	}

	class XorshiroStarStar256 : public Rng64Bits
	{
	public:
		XorshiroStarStar256(BigNatural);
		XorshiroStarStar256();
		void reset() override;
		BigNatural next() override;
	private:
		BigNaturalArray _s;

		BigNatural rol64(BigNatural x, Integer k);
	};

	inline BigNatural XorshiroStarStar256::rol64(BigNatural x, Integer k)
	{
		return (x << k) | (x >> (64 - k));
	}
}