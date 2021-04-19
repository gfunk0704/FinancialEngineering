#pragma once
#include <rng_32bits.h>

namespace FinancialEngineering
{
	namespace Uniform
	{
		inline Real next_real_uniform(SharedPointer<Rng32Bits> rng)
		{
			return (rng->next() * 2.32830643653869628906e-010);
		}

		inline RealArray next_real_uniform(SharedPointer<Rng32Bits> rng, Natural n)
		{
			RealArray random(n);
			for (Real* iter = random.data(); iter != (random.data() + n); ++iter)
			{
				(*iter) = next_real_uniform(rng);
			}
			return random;
		}

		inline Natural next_natural_uniform(SharedPointer<Rng32Bits> rng, Natural sup)
		{
			Natural divisor = ((-sup) / sup) + 1;
			for (;;) {
				Natural value = rng->next() / divisor;
				if (value < sup)
					return value;
			};
		}
	}
}