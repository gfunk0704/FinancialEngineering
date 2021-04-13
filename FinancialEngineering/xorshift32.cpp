#include <xorshift32.h>

namespace FinancialEngineering
{
	Xorshift32::Xorshift32(Natural seed) :
		Rng32Bits(seed), _s(seed)
	{}

	Xorwow::Xorwow(Natural seed) :
		Rng32Bits(seed)
	{
		reset();
	}

	void Xorwow::reset()
	{
		Xorshift32 rng(_seed);
		_a = rng.next();
		_b = rng.next();
		_c = rng.next();
		_d = rng.next();
		_e = rng.next();
		_counter = 6615241;
	}

	Natural Xorwow::next()
	{
		Natural t = _e;
		Natural s = _a;
		_e = _d;
		_d = _c;
		_c = _b;
		_b = s;
		t ^= t >> 2;
		t ^= t << 1;
		t ^= s ^ (s << 4);
		_a = t;
		_counter += 362437;
		return t + _counter;
	}

	void Xorwow::status()
	{
		std::cout << "seed: " << _seed << std::endl;
		std::cout << "a: " << _a << std::endl;
		std::cout << "b: " << _b << std::endl;
		std::cout << "c: " << _c << std::endl;
		std::cout << "d: " << _d << std::endl;
		std::cout << "e: " << _e << std::endl;
		std::cout << "counter: " << _counter << std::endl;
	}
}