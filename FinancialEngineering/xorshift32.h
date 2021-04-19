#pragma once

#include <rng_32bits.h>
#include <global_variable.h>

namespace FinancialEngineering
{
	class Xorshift32 : public Rng32Bits
	{
	public:
		Xorshift32(Natural);
		Xorshift32();
		SharedPointer<Rng32Bits> clone_pointer() override;
		void reset() override;
		Natural next() override;
		void status() override;
	private:
		Natural _s;
	};

	inline SharedPointer<Rng32Bits> Xorshift32::clone_pointer()
	{
		return SharedPointer<Rng32Bits>(new Xorshift32(_seed));
	}

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
		SharedPointer<Rng32Bits> clone_pointer() override;
		void reset() override;
		Natural next() override;
		void status() override;
	private:
		Natural _a, _b, _c, _d, _e;
		Natural _counter;
	};

	inline SharedPointer<Rng32Bits> Xorwow::clone_pointer()
	{
		return SharedPointer<Rng32Bits>(new Xorwow(_seed));
	}
}