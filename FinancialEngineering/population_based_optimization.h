#pragma once

#include <optimization.h>
#include <rng_32bits.h>
#include <uniform.h>
#include <global_variable.h>

namespace FinancialEngineering
{
	class PopulationBasedOptimization : public Optimization
	{
	public:
		PopulationBasedOptimization(SharedPointer<Rng32Bits>);
	protected:
		SharedPointer<Rng32Bits> _rng;

		std::vector<RealArray> generate_samples(Natural, RealArray, RealArray);
	};

	
}