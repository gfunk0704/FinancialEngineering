#include <simulator.h>

namespace FinancialEngineering
{
	Simulator::Simulator(SharedPointer<Gaussian> gaussian_rng,
		                 SharedPointer<NonparametricYieldTermStructure> term_structure):
		_gaussian_rng(gaussian_rng), 
		_term_structure(term_structure)
	{}

	SimulationSample Simulator::generate_random_numbers(Natural step)
	{
		Natural n_sample = GlobalVariable::get_simulation_path();
		SimulationSample random;
		while (step > 0)
		{
			RealEigenArray step_random(n_sample);
			for (Size i = 0; i < n_sample; i++)
			{
				step_random(i) = _gaussian_rng->next_gaussian();
			}
			random.push_back(step_random);
			--step;
		}
		return random;
	}
}