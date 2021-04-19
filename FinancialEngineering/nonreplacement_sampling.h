#pragma once

#include <rng_32bits.h>
#include <uniform.h>

namespace FinancialEngineering
{
	namespace NonreplacementSampling
	{
		NaturalArray sampling(SharedPointer<Rng32Bits>, Natural, Natural);
	};
}