#include <xorshift32.h>

namespace FinancialEngineering
{
	Xorshift32::Xorshift32(Natural seed) :
		Rng32Bits(seed)
	{
		reset();
	}

	Xorshift32::Xorshift32():
		Xorshift32((Natural)GlobalVariable::get_seed())
	{}

	Xorrow::Xorrow(Natural seed) :
		Rng32Bits(seed)
	{
		reset();
	}

	Xorrow::Xorrow() :
		Xorrow((Natural)GlobalVariable::get_seed())
	{}

	void Xorrow::reset()
	{
		Xorshift32 rng(_seed);
		_a = rng.next();
		_b = rng.next();
		_c = rng.next();
		_d = rng.next();
		_e = rng.next();
		_counter = rng.next();
	}

	Natural Xorrow::next()
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
}