#pragma once
#include <rng_32bits.h>

namespace FinancialEngineering
{
	class RealUniform
	{
	public:
		static Real next_uniform(SharedPointer<Rng32Bits>);
	};

	inline Real RealUniform::next_uniform(SharedPointer<Rng32Bits> rng)
	{
		return (rng->next() * 2.32830643653869628906e-010);
	}

	class NaturalUniform
	{
	public:
		static Natural next_uniform(SharedPointer<Rng32Bits>, Natural);
	};

	inline Natural NaturalUniform::next_uniform(SharedPointer<Rng32Bits> rng, Natural sup)
	{
		Natural divisor = ((-sup) / sup) + 1;
		for (;;) {
			Natural value = rng->next() / divisor;
			if (value < sup)
				return value;
		};
	}
}