#include <population_based_optimization.h>

namespace FinancialEngineering
{
	PopulationBasedOptimization::PopulationBasedOptimization(SharedPointer<Rng32Bits> rng):
		_rng(rng)
	{}
	
	std::vector<RealArray> PopulationBasedOptimization::generate_samples(Natural n, RealArray lower, RealArray upper)
	{
		std::vector<RealArray> samples;
		RealArray interval = upper - lower;
		Natural d = upper.size();
		for (Natural i = 0; i < n; i++)
		{
			RealArray new_sample = lower + interval * Uniform::next_real_uniform(_rng, d);
			samples.push_back(new_sample);
		}
		return samples;
	}
}