#pragma once

#include <rng_32bits.h>

namespace FinancialEngineering
{
	class Xorshift32 : public Rng32Bits
	{
	public:
		Xorshift32(Natural);
		Xorshift32();
		void reset() override;
		Natural next() override;
		void status() override;
	private:
		Natural _s;
	};

	inline void Xorshift32::reset()
	{
		_s = _seed;
	}

	inline Natural Xorshift32::next()
	{
		_s ^= _s << 13;
		_s ^= _s >> 17;
		_s ^= _s << 5;
		return _s;
	}

	inline void Xorshift32::status()
	{
		std::cout << "seed: " << _seed << std::endl;
		std::cout << "s: " << _s << std::endl;
	}

	class Xorwow : public Rng32Bits
	{
	public:
		Xorwow(Natural);
		Xorwow();
		void reset() override;
		Natural next() override;
		void status() override;
	private:
		Natural _a, _b, _c, _d, _e;
		Natural _counter;
	};
}