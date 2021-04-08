#pragma once

#include <rng_32bits.h>
#include <uniform.h>

namespace FinancialEngineering
{
	class NonreplacementSampling
	{
	public:
		NonreplacementSampling(NaturalUniform);
		void reset();
		NaturalArray sampling(Natural, Natural);
	private:
		NaturalUniform _uniform;
	};

	inline void NonreplacementSampling::reset()
	{
		_uniform.reset();
	}
}