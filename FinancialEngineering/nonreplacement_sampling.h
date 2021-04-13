#pragma once

#include <rng_32bits.h>
#include <uniform.h>

namespace FinancialEngineering
{
	class NonreplacementSampling
	{
	public:
		static NaturalArray sampling(SharedPointer<Rng32Bits>, Natural, Natural);
	};
}